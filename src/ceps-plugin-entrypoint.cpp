/*
    v2g-guru-exi - an EXI (= "Efficient XML Interchange") processor
    Copyright (C) 2022 Tomas Prerovsky <cepsdev@hotmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <chrono>
#include <sstream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <future>
#include <netinet/sctp.h> 

#include "v2g-guru-exi.h"

namespace v2g_guru_exi{
    static Ism4ceps_plugin_interface* plugin_master = nullptr;
    static const std::string version_info = "v2g-guru-exi v0.1";
    static constexpr bool print_debug_info{true};
    static Processor exi_processor; 
    ceps::ast::node_t plugin_entrypoint_add_start_grammar(ceps::ast::node_callparameters_t params);
    ceps::ast::node_t plugin_entrypoint_encode (ceps::ast::node_callparameters_t params);
    ceps::ast::node_t plugin_entrypoint_add_generic_grammar(ceps::ast::node_callparameters_t params);
    ceps::ast::node_t plugin_entrypoint_operation(ceps::ast::node_callparameters_t params);
}

static bool expect_nonterminal(ceps::ast::Nodeset ns){
    using namespace ceps::ast;
    return ns.nodes().size() == 1 && 
           is<Ast_node_kind::symbol>(ns.nodes()[0]) &&
           kind(as_symbol_ref(ns.nodes()[0])) == "GrammarNonterminal"
           ;
}

static bool expect_terminal(ceps::ast::Nodeset ns){
    using namespace ceps::ast;
    return ns.nodes().size() == 1 && 
           v2g_guru_exi::Grammar::Terminal{ns.nodes()[0]}.valid();
}

static bool expect_one_and_only_one_grammar(ceps::ast::Nodeset ns){
    using namespace ceps::ast;
    return ns[all{"Grammar"}].nodes().size() == 1;
}

static bool expect_two_grammars(ceps::ast::Nodeset ns){
    using namespace ceps::ast;
    return ns[all{"Grammar"}].nodes().size() == 2;
}

static bool expect_lhs(ceps::ast::Nodeset ns){
    using namespace ceps::ast;
    
    return ns[all{"lhs"}].nodes().size() == 1 && ns["lhs"].nodes().size() == 1 && 
           is<Ast_node_kind::symbol>(ns["lhs"].nodes()[0]) &&
           kind(as_symbol_ref(ns["lhs"].nodes()[0])) == "GrammarNonterminal"
           ;
}


static void v2g_guru_exi_err(std::string msg){
    std::cerr << "*** Fatal Error [v2g-guru-exi] " <<  msg << "\n";
}

ceps::ast::node_t v2g_guru_exi::plugin_entrypoint_operation(ceps::ast::node_callparameters_t params){
    auto data = get_first_child(params);    
    if (!is<Ast_node_kind::structdef>(data)) return nullptr;
    auto& ceps_struct = *as_struct_ptr(data);
    if("rename_non_terminal" == name(ceps_struct))
    {
        auto ns = ceps::ast::Nodeset{children(ceps_struct)};
        if(!expect_nonterminal(ns["from"])) {   v2g_guru_exi_err (" exi_processor_operation() argument 'from': expected exactly one non-terminal (symbol of kind GrammarNonterminal)."); 
                                                return nullptr;}
        if(!expect_nonterminal(ns["to"])) {   v2g_guru_exi_err (" exi_processor_operation()  argument 'to': expected exactly one non-terminal (symbol of kind GrammarNonterminal)."); 
                                                return nullptr;}
        if(!expect_one_and_only_one_grammar(ns)) {   v2g_guru_exi_err (" exi_processor_operation() argument 'Grammar': expected exactly one grammar (a single struct with name 'Grammar')."); 
                                                return nullptr;}
        auto from_nt = Grammar::NonTerminal{ns["from"].nodes()[0]};
        auto to_nt = Grammar::NonTerminal{ns["to"].nodes()[0]};
        auto g = Grammar{ns[all{"Grammar"}].nodes()[0]};
        g.rename_non_terminal(from_nt.name(), to_nt.name());
        return g.grammar_rep;
    }
    else if("rename_terminal_to_nonterminal" == name(ceps_struct))
    {
        auto ns = ceps::ast::Nodeset{children(ceps_struct)};
        if(!expect_terminal(ns["from"])) {   v2g_guru_exi_err (" exi_processor_operation(op = rename_terminal_to_nonterminal) argument 'from': expected exactly one terminal (symbol of kind GrammarNonterminal)."); 
                                                return nullptr;}
        if(!expect_nonterminal(ns["to"])) {   v2g_guru_exi_err (" exi_processor_operation(op = rename_terminal_to_nonterminal)  argument 'to': expected exactly one non-terminal (symbol of kind GrammarNonterminal)."); 
                                                return nullptr;}
        if(!expect_one_and_only_one_grammar(ns)) {   v2g_guru_exi_err (" exi_processor_operation(op = rename_terminal_to_nonterminal) argument 'Grammar': expected exactly one grammar (a single struct with name 'Grammar')."); 
                                                return nullptr;}
        auto from_t = Grammar::Terminal{ns["from"].nodes()[0]};
        auto to_nt = Grammar::NonTerminal{ns["to"].nodes()[0]};
        auto g = Grammar{ns[all{"Grammar"}].nodes()[0]};
        g.rename_terminal_to_nonterminal(from_t.name(), to_nt.name());
        return g.grammar_rep;
    }
    else if ("get_nonterminals_on_lhs" == name(ceps_struct))
    {
        auto ns = ceps::ast::Nodeset{children(ceps_struct)};
        if(!expect_one_and_only_one_grammar(ns)) {   v2g_guru_exi_err (" exi_processor_operation(op = "+name(ceps_struct)+") argument 'Grammar': expected exactly one grammar (a single struct with name 'Grammar')."); 
                                                return nullptr;}
        auto g = Grammar{ns[all{"Grammar"}].nodes()[0]};
        auto r = g.get_lhs_nonterminals();
        auto ceps_r = ceps::ast::mk_scope();
        for(auto e:r){
            children(*ceps_r).push_back(e.get_rep()->clone());
        }
        return ceps_r;
    }
    else if("get_conflicting_nonterminals" == name(ceps_struct)){
        auto ceps_r = ceps::ast::mk_scope();
        auto ns = ceps::ast::Nodeset{children(ceps_struct)};
        if(!expect_two_grammars(ns)) {   v2g_guru_exi_err (" exi_processor_operation(op = "+name(ceps_struct)+") argument 'Grammar': expect two grammars (two 'Grammar'-structs)."); 
                                                return nullptr;}

        auto g1 = Grammar{ns[all{"Grammar"}].nodes()[0]};
        auto g2 = Grammar{ns[all{"Grammar"}].nodes()[1]};
        
        auto r = g1.confliciting_nonterminals(g2);
        for(auto e: r){
            children(*ceps_r).push_back(e.get_rep()->clone());   
        }
    
        return ceps_r;
    }
    else if("resolve_conflicting_nonterminals" == name(ceps_struct)){
        auto ceps_r = ceps::ast::mk_scope();
        auto ns = ceps::ast::Nodeset{children(ceps_struct)};
        if(!expect_two_grammars(ns)) {   v2g_guru_exi_err (" exi_processor_operation(op = "+name(ceps_struct)+") argument 'Grammar': expect two grammars (two 'Grammar'-structs)."); 
                                                return nullptr;}

        auto g1 = Grammar{ns[all{"Grammar"}].nodes()[0]};
        auto g2 = Grammar{ns[all{"Grammar"}].nodes()[1]};
        
        auto r = g1.resolve_conflicting_nonterminals(g2);
        for(auto e: r){
            auto r = ceps::ast::mk_scope();
            children(*r).push_back(e.first.get_rep()->clone());
            children(*r).push_back(e.second.get_rep()->clone());
            children(*ceps_r).push_back(
                r
            );
        }   
    } else if ("concatenate_grammars"  == name(ceps_struct)){
            auto ns = ceps::ast::Nodeset{children(ceps_struct)};
            if(!expect_two_grammars(ns)) {   
                v2g_guru_exi_err (" exi_processor_operation(op = "+name(ceps_struct)+") argument 'Grammar': expect two grammars (two 'Grammar'-structs)."); 
                return nullptr;
            }
            auto g1 = Grammar{ns[all{"Grammar"}].nodes()[0]};
            auto g2 = Grammar{ns[all{"Grammar"}].nodes()[1]};
            
            g1.concatenate(g2);
            return g1.grammar_rep;
    } else if ("create_element_grammar" == name(ceps_struct)){
            auto ns = ceps::ast::Nodeset{children(ceps_struct)};
            if(!expect_one_and_only_one_grammar(ns)) {   
                v2g_guru_exi_err (" exi_processor_operation(op = "+name(ceps_struct)+") argument 'Grammar': expect one grammar (one 'Grammar'-struct)."); 
                return nullptr;
            }
            if (!expect_lhs(ns)){
                v2g_guru_exi_err (" exi_processor_operation(op = "+name(ceps_struct)+") argument 'lhs': expect one lhs (one 'lhs'-struct containing exactly one non-terminal)."); 
                return nullptr;                
            }
            Grammar g{ns[all{"Grammar"}].nodes()[0]};
            Grammar::NonTerminal nt{ns["lhs"].nodes()[0]};
            Grammar result{nt,g};
            return result.get_rep(); 
    }
    
    v2g_guru_exi_err (" exi_processor_operation() operation '"+name(ceps_struct)+"' not supported.");
    return nullptr;
}

ceps::ast::node_t v2g_guru_exi::plugin_entrypoint_add_start_grammar(ceps::ast::node_callparameters_t params){
    auto data = get_first_child(params);
    
    if (!is<Ast_node_kind::structdef>(data)) return nullptr;
    auto& ceps_struct = *as_struct_ptr(data);
    if("Grammar" != name(ceps_struct)) return nullptr;
    Grammar g{data};

    if(v2g_guru_exi::print_debug_info){
        std::cout << "plugin_entrypoint_add_start_grammar(G) where G = { \n";
        auto v_lhs = g.left_hand_sides();
        for(auto p : v_lhs) {
            std::cout << "  " << p.name() << ":\n";
            auto v_rhs = g.right_hand_sides(p);
            /*if (v_rhs.size()){ 
                for(auto pp : v_rhs)
                    std::cout << "    " << pp.get_lhs().name() << "\n";
            }*/
        }
        std::cout << "\n}\n"; 
    }
    
    exi_processor.set_start_grammar(g);
    
    return nullptr;
}

ceps::ast::node_t v2g_guru_exi::plugin_entrypoint_encode (ceps::ast::node_callparameters_t params){
    auto data = get_first_child(params);
    auto result = mk_struct("encoding");
    
    if (!is<Ast_node_kind::structdef>(data)) return result;
    auto& ceps_struct = *as_struct_ptr(data);
    if("events" != name(ceps_struct)) return result;
    ceps_emitter emitter{result};

    exi_processor.set_emitter(&emitter);
    exi_processor.set_event_stream(EventStream{children(ceps_struct)});
    exi_processor.encode();
    return result;
}

ceps::ast::node_t v2g_guru_exi::plugin_entrypoint_add_generic_grammar(ceps::ast::node_callparameters_t params){
    auto data = get_first_child(params);    
    if (!is<Ast_node_kind::structdef>(data)) return nullptr;
    auto& ceps_struct = *as_struct_ptr(data);
    if("GenericGrammar" != name(ceps_struct)) {
        std::cerr << "*** Error (v2g-guru-exi processor: add_generic_grammar()): Invalid argument. Expect GenericGrammar{Pattern{...}; Grammar{...};}.\n"; 
        return nullptr;
    }
    exi_processor.insert(GenericGrammar{data});
    return nullptr;
}

void v2g_guru_exi::ceps_emitter::emit(Grammar::EventCode ev) {
    if (!encoding_result) return;
    if (ev.dim == 0)
        children(as_struct_ref(encoding_result)).push_back(
            new Func_call(
                new Identifier("EventCode",nullptr,nullptr,nullptr),
                new Call_parameters()        
            )
        );
    else if (ev.dim == 1)
        children(as_struct_ref(encoding_result)).push_back(
            new Func_call(
                new Identifier("EventCode",nullptr,nullptr,nullptr),
                new Call_parameters(ceps::interpreter::mk_int_node(ev.code[0]))        
            )
        );
     else if (ev.dim == 2)
        children(as_struct_ref(encoding_result)).push_back(
            new Func_call(
                new Identifier("EventCode",nullptr,nullptr,nullptr),
                new Call_parameters(
                   ceps::interpreter::mk_bin_op ( ',', 
                        ceps::interpreter::mk_int_node(ev.code[0]),
                        ceps::interpreter::mk_int_node(ev.code[1]),"")
                )        
            )
        );
     else if (ev.dim >= 3)
        children(as_struct_ref(encoding_result)).push_back(
            new Func_call(
                new Identifier("EventCode",nullptr,nullptr,nullptr),
                new Call_parameters(
                   ceps::interpreter::mk_bin_op (',',
                    ceps::interpreter::mk_bin_op ( ',', 
                            ceps::interpreter::mk_int_node(ev.code[0]),
                            ceps::interpreter::mk_int_node(ev.code[1]),""
                    ),ceps::interpreter::mk_int_node(ev.code[2]),"")

                )        
            )
        );
}


extern "C" void init_plugin(IUserdefined_function_registry* smc)
{
  v2g_guru_exi::plugin_master = smc->get_plugin_interface();
  v2g_guru_exi::plugin_master->reg_ceps_plugin("exi_processor_add_start_grammar", v2g_guru_exi::plugin_entrypoint_add_start_grammar);
  v2g_guru_exi::plugin_master->reg_ceps_plugin("exi_processor_encode", v2g_guru_exi::plugin_entrypoint_encode);
  v2g_guru_exi::plugin_master->reg_ceps_plugin("exi_processor_add_generic_grammar", v2g_guru_exi::plugin_entrypoint_add_generic_grammar);
  v2g_guru_exi::plugin_master->reg_ceps_phase0plugin("exi_processor_operation", v2g_guru_exi::plugin_entrypoint_operation);

  if(v2g_guru_exi::print_debug_info) std::cout << v2g_guru_exi::version_info << " registered.\n";
}

