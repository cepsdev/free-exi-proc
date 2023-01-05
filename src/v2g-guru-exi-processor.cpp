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

#include "v2g-guru-exi.h"


namespace v2g_guru_exi{
    
    void Processor::insert(GenericGrammar g){
        generic_grammars[g.pattern_to_str()] = g.get_grammar();

    }                     
 
    void Processor::set_start_grammar(Grammar g){
        grammars = stack<Grammar>{};
        grammars.push(g);
    }
    
    void Processor::set_event_stream(EventStream ev_stream){
        event_stream = ev_stream;
    }

    bool Processor::match(Grammar::Terminal terminal){
         auto tok = event_stream.get_event().as_terminal();
         if (debug_output)  
            cout << " match( " << terminal << "," << tok <<")="<< ( tok == terminal)<< "\n";
         bool eq = tok == terminal;
         if (eq) last_match = tok;
         return eq;                 
    }

    void Processor::emit_eventcode(Grammar& g, Grammar::Production prod){
        if(!emitter) return;
        for(auto it = prod.begin(); it != prod.end(); ++it){
            if (!(*it).is_eventcode()) continue;
            auto ev_code{(*it).as_eventcode()};
            emitter->emit(ev_code);
            if (debug_output_emit_eventcode)std::cout << "    EMIT: " << ev_code << "\n" ; //<< g << "\n"; 
            break;
        }
    }

    bool Processor::parse(Grammar g, Grammar::Production prod) {
        auto prologue = [&](){
            if (debug_output) 
                std::cout << "Processor::parse(Grammar& g, Grammar::Production prod):\n";
            if (debug_output) 
                std::cout << "  " << *prod.get_lhs().get_rep() << ": " << *prod.get_rhs_rep() << "\n"; 
            if (debug_output) std::cout << "  peek = " <<  *event_stream.peek().get_rep() << "\n\n\n";
        };

        auto find_production_starting_with_lookahead = [&](Grammar::NonTerminal nt) -> optional< pair<Grammar::Production, Grammar::Terminal>  > {
                auto nt_rhs = g.right_hand_sides(nt);
                if (nt_rhs.size() == 0) return {};
                auto lookahead = event_stream.peek();
                if (!lookahead) throw parser_exception{};                
                for(auto prod : nt_rhs){
                    for(auto entry : prod){
                        if (entry.is_annotation()) continue;
                        if (entry.is_nonterminal()) break;
                        if (entry.as_terminal() == lookahead.as_terminal()) return make_pair(prod,entry.as_terminal());
                    }
                }
                return {};
        };

        auto gen_err_text = [&](Event lookahead, Grammar::Production prod) -> string {
            stringstream ss;

            ss << "\n   Details:\n";
            ss << "     lookahead         = " << *lookahead.get_rep() << "\n";
            ss << "     Active production = " << prod << "\n"; 
            ss << "    " << g << "\n"; 

            
            return ss.str();
        };
        
        auto handle_content = [&](Event const & ev) -> void{
            auto uri = ev.get_uri();
            if (uri){
                auto const & v = *uri;
                
            }
        };

        prologue();
        if (get_last_match().valid()) 
         std::cout <<*get_last_match().get_rep() << "\n"; else  std::cout << "???\n";
        emit_eventcode(g, prod);
        handle_content(event_stream.peek());

        for(auto rhs_elem : prod){             
            if (debug_output) std::cout << " parse: checking " << *rhs_elem.rep << ": " << " terminal? " << rhs_elem.is_terminal() << " nonterminal? " << rhs_elem.is_nonterminal() << "\n";
            auto lookahead = event_stream.peek();
            if (rhs_elem.is_terminal()){  
                if (debug_output) 
                  std::cout << "=======> match( lookahead="<< *lookahead.get_rep() << ", " << *rhs_elem.rep << ")\n";
                if (!match(rhs_elem.as_terminal())) throw parser_exception{"match failed."};

                //std::cout << "g.has_global_id(): " << g.has_global_id() << " g.is_modifiable(): " << g.is_modifiable() << " prod.is_generic(): "<< prod.is_generic() << "\n";
                //std::cout << *prod.get_rhs_rep()<<"\n";
                int gen_type = 0;
                if (g.has_global_id() && g.is_modifiable() && prod.is_generic(gen_type)){
                    //std::cout << "\n\n\n=========>generic rule\n\n\n\n";
                    bool perform_instantiation = false;
                    if (gen_type == Grammar::Production::GENERIC_IF_EVCODE_LEN_NOT_ONE){
                        auto ev = prod.get_eventcode();
                        if (!ev) perform_instantiation = true;
                        else{
                            if (ev->dim <= 1) perform_instantiation = true;
                        }
                    } perform_instantiation = true;
                    if (perform_instantiation){
                        auto new_prod = prod.instantiate(lookahead.as_terminal());
                        if (!new_prod) continue;
                        //std::cout << *new_prod << "\n\n\n";
                        auto ev = new_prod->get_eventcode();
                        if (!ev) continue;
                        
                        //std::cout << "\n\n\n\n Original:"<< "\n******************************************************************************************\n\n";
                        //std::cout << g << "\n\n\n\n";
                        
                        g.insert(*new_prod);
                        global_grammars[g.global_id()] = g;

                        //std::cout << "\n\n\n\n Modified:"<< "\n******************************************************************************************\n\n";
                        //std::cout << g << "\n\n\n\n";
                    }
                }  
                

                { /*handle cases like SE(*)*/
                    auto sgrammar_id = lookahead.as_terminal().as_str();
                    auto it_gg = generic_grammars.find(rhs_elem.as_terminal().as_str());
                    if (it_gg != generic_grammars.end() ){
                        // We found a generic grammar:
                        // An example of a generic grammar is the BuiltinElementGrammar it has the id SE(_*_)
                        // We instantiate the generic grammar with the current event stored in lookahead.
                        auto it_global_g = global_grammars.find(sgrammar_id);
                        if (it_global_g == global_grammars.end()){
                            Grammar new_g{it_gg->second};
                            new_g.global_id() = sgrammar_id;
                            //std::cout << "new_g.global_id() = >>> " << new_g.global_id() << "<<< \n"; 
                            global_grammars[sgrammar_id] = new_g;
                            it_global_g = global_grammars.find(sgrammar_id);
                        }
                        parse(it_global_g->second);
                    } else {
                        auto it_global_g = global_grammars.find(sgrammar_id);
                        if (it_global_g != global_grammars.end())
                         parse(it_global_g->second);
                    }
                }
            } else if (rhs_elem.is_nonterminal()){
                auto nt = rhs_elem.as_nonterminal();
                auto mp = find_production_starting_with_lookahead(nt);
                if (!mp) throw parser_exception{"Rule for '"+nt.name()+"' missing. "+gen_err_text(lookahead,prod)};
                auto matching_production = mp->first;
                if (!parse(g, matching_production)) return false;
            } else if (rhs_elem.is_action()){
                if(rhs_elem.as_action().action_name() == "PopGrammar") return false;
            }
        }
        return true;
    }

    void Processor::parse(Grammar g){
        auto gen_err_text = [&]() -> string {
            stringstream ss;

            ss << "\n   Details:\n";
            ss << "     lookahead         = " << *event_stream.peek().get_rep() << "\n";
            ss << "    " << g << "\n"; 

            return ss.str();
        };

        if (debug_output)std::cout << "Processor::parse(Grammar& g)\n";
        if (debug_output)std::cout << "G=\n";
        if (debug_output)std::cout << *g.grammar_rep << std::endl;
        for (;event_stream;){
             auto tok = event_stream.peek();
             if (!tok) throw parser_exception{};
             if (debug_output) std::cout << "tok=" << *tok.get_rep() << "\n";
             auto production = g.find_production_starting_with(tok.as_terminal());
             if (!production) return;//throw parser_exception{"parse(G): No rule found. " + gen_err_text()};
             if(!parse(g,*production)) break;
        }
    }

    void Processor::encode(){
        bool error_occured{};
        if (debug_output)std::cout << "Processor::encode():\n";
        while(grammars.size() && !error_occured){
            auto current_grammar = grammars.top();
            grammars.pop();
            try{
                parse(current_grammar);
            } catch (parser_exception& pe){
                std::cerr << "*** Fatal Error [EXI Processor]: " << pe.msg << std::endl;
                error_occured = true;
            }
        }
        if (debug_output) std::cout << "Processor::encode(): exit.\n";
    }
}