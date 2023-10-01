/*
    free-exi-proc - an EXI (= "Efficient XML Interchange") processor
    Copyright (C) 2023 Tomas Prerovsky <cepsdev@hotmail.com>

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
#include "v2g-guru-exi.h"
#include "free-exi-terminal.h"
#include "v2g-guru-exi-model-adapter.h"

#include <unordered_map>
#include<string>

namespace v2g_guru_exi{

    static void build_term_default(node_t, Grammar::Terminal&){

    }

    extern std::unordered_map<std::string, Grammar::Terminal::ev_type_t> ev_type_encoding;
    extern std::unordered_map<Grammar::Terminal::ev_type_t, std::string> ev_type_encoding_rev;

    static std::string term_sym_kind{"GrammarTerminal"};
    
    static std::unordered_map<Grammar::Terminal::ev_type_t, 
                              void (*)(node_t, Grammar::Terminal&)> 
     factories_pure_terminal
     {
        {{},build_term_default}
     }; 
    static std::unordered_map<Grammar::Terminal::ev_type_t, 
                              void (*)(node_t, Grammar::Terminal&)> 
     factories_parameterized_terminal;
    
    static void build_se_at_term_helper (node_t rep, Grammar::Terminal& t) {
        string sym_name;string sym_kind;vector<node_t> args;
        if (is_a_symbol_with_arguments(rep,sym_name,sym_kind,args)){
            if (sym_kind != term_sym_kind) return;
                if (args.size() && is<Ast_node_kind::binary_operator>(args[0]) && ":" == op_val(as_binop_ref(args[0])) ){
                    t.qualified = true;
                    auto l{children(as_binop_ref(args[0]))[0]};
                    auto r{children(as_binop_ref(args[0]))[1]};
                    if (is<Ast_node_kind::string_literal>(r) && is<Ast_node_kind::string_literal>(l)){
                        t.qname.uri = value(as_string_ref(l));
                        t.qname.local_name = value(as_string_ref(r));
                        t.qname.prefix = {}; 
                    } else if (is<Ast_node_kind::binary_operator>(r) && "*" == op_val(as_binop_ref(r)) && is<Ast_node_kind::string_literal>(l)){
                        t.qname.uri = value(as_string_ref(l));
                        t.qname.local_name = {};
                        t.qname.prefix = {}; 
                    }
                } else if (args.size() && is<Ast_node_kind::binary_operator>(args[0]) && "*" == op_val(as_binop_ref(args[0])) ){
                    t.qualified = true;
                    t.qname = {};
                }
        }
    }

    void init_model_structures(){
        factories_pure_terminal = {
            {{},build_term_default},
            {ev_type_encoding["ED"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::ED;} },
            {ev_type_encoding["SD"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::SD;} },
            {ev_type_encoding["SE"], [] (node_t rep, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::SE;build_se_at_term_helper(rep,t);} },
            {ev_type_encoding["EE"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::EE;} },
            {ev_type_encoding["AT"], [] (node_t rep, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::AT;build_se_at_term_helper(rep,t);} },
            {ev_type_encoding["CH"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::CH;} },
            {ev_type_encoding["NS"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::NS;} },
            {ev_type_encoding["CM"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::CM;} },
            {ev_type_encoding["PI"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::PI;} },
            {ev_type_encoding["DT"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::DT;} },
            {ev_type_encoding["ER"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::ER;} },
            {ev_type_encoding["SC"], [] (node_t, Grammar::Terminal& t) -> void {t.ev_type = Grammar::Terminal::SC;} }
        };
    }



    template<> node_t ast_rep(Grammar::Terminal t){
        if (!t.qualified){
            return ceps::ast::mk_symbol(ev_type_encoding_rev[t.ev_type],term_sym_kind);            
        } else {
            if (!t.qname.uri  && !t.qname.local_name)
            {
                return mk_function( 
                        ceps::ast::mk_symbol(ev_type_encoding_rev[t.ev_type] ,term_sym_kind), { mk_binary_op("*",mk_identifier("_"), mk_identifier("_"))});

            } else if (t.qname.uri && !t.qname.local_name){
                return mk_function( 
                        ceps::ast::mk_symbol(ev_type_encoding_rev[t.ev_type] ,term_sym_kind), { mk_binary_op(":",mk_string(*t.qname.uri), mk_binary_op("*",mk_identifier("_"), mk_identifier("_"))  )});
            } else if (t.qname.uri && t.qname.local_name){
                auto op_cont{t.get_content()};
                if (!op_cont){
                    return mk_function( 
                        ceps::ast::mk_symbol(ev_type_encoding_rev[t.ev_type] ,term_sym_kind), { mk_binary_op(":",mk_string(*t.qname.uri), mk_string(*t.qname.local_name))});
                }
            }
        }
        return mk_undef("ast_rep(Terminal) failed");
    }

    Grammar::Terminal::Terminal(grammar_elem_t rep_arg) {
        string err_prefix = "Failed to construct Grammar::Terminal::Terminal: ";
        auto build_terminal = [&](Symbol& sym){
            if (kind(sym) != term_sym_kind) 
             throw std::invalid_argument{err_prefix+" unknown kind '"+kind(sym)+"'"};
            auto ev_type_it {ev_type_encoding.find( ceps::ast::name(sym))};
            if (ev_type_it == ev_type_encoding.end()) 
             throw std::invalid_argument{err_prefix+" unknown event type '"+ceps::ast::name(sym)+"'"};
            ev_type = ev_type_it->second;
            auto factory_it{factories_pure_terminal.find(ev_type)};
            if (factory_it == factories_pure_terminal.end()) 
             throw std::runtime_error{err_prefix+" no factory found for '"+ceps::ast::name(sym)+"'"};
            factory_it->second(rep_arg,*this);
        };

        if (!rep_arg) throw std::invalid_argument{"Terminal(null)"};
        if (is<Ast_node_kind::symbol>(rep_arg)){
            auto& sym{as_symbol_ref(rep_arg)};
            build_terminal(sym);
        } else if (
            is<Ast_node_kind::func_call>(rep_arg) && 
            is<Ast_node_kind::symbol>(func_call_target(as_func_call_ref(rep_arg))) && 
            kind(as_symbol_ref(func_call_target(as_func_call_ref(rep_arg)))) == term_sym_kind  ) {
            build_terminal(as_symbol_ref(func_call_target(as_func_call_ref(rep_arg))));
        }
    }
    
}