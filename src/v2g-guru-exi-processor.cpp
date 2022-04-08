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
 
    void Processor::set_start_grammar(Grammar g){
        grammars = stack<Grammar>{};
        grammars.push(g);
    }
    
    void Processor::set_event_stream(EventStream ev_stream){
        event_stream = ev_stream;
    }

    bool  Processor::match(Grammar::Terminal terminal){
         auto tok = event_stream.get_event().as_terminal();
         return tok == terminal;                 
    }

    void Processor::parse(Grammar& g, Grammar::Production prod){
        for(auto it = prod.begin(); it != prod.end(); ++it) {
            auto rhs_elem = *it;
            if (rhs_elem.is_terminal()){                
                if (!match(rhs_elem.as_terminal())) throw parser_exception{};
            } else if (rhs_elem.is_nonterminal()){
                auto nt = rhs_elem.as_nonterminal();
                auto nt_rhs = g.right_hand_sides(nt);
                if (nt_rhs.size()){
                    auto lookahead = event_stream.peek();
                    if (!lookahead) throw parser_exception{};
                    bool prod_found{};
                    for(auto prod : nt_rhs){
                        for(auto entry : prod){
                            if (entry.is_annotation()) continue;
                            if (entry.is_nonterminal()) break;
                            if (entry.as_terminal() == lookahead.as_terminal()){
                                prod_found = true;
                                break;                                
                            }
                        }
                        if (prod_found) {
                            parse(g, prod);
                            break;
                        }
                    }
                    if (!prod_found) throw parser_exception{"Missing rule.(A)"};
                    
                } else throw parser_exception{"Missing rule.(B)"};
            }
        }
    }

    void Processor::parse(Grammar& g){
        for (;event_stream;){
             auto tok = event_stream.peek();
             if (!tok) throw parser_exception{};
             auto production = g.find_production_starting_with(tok.as_terminal());
             if (!production) break;
             parse(g,*production);
        }
    }

    void Processor::encode(){
        bool error_occured{};
        std::cout << "Processor::encode():\n";
        while(grammars.size() && !error_occured){
            auto current_grammar = grammars.top();
            grammars.pop();
            try{
                parse(current_grammar);
            } catch (parser_exception& pe){
                std::cerr << "*** Fatal Error [EXI Processor]: " << pe.msg << std::endl;
                error_occured = true;
            }
           /* for (;event_stream && !error_occured;){
                auto tok = event_stream.peek();
                //std::cout << "  fetched event.\n";
                if (!tok) break;
                    //std::cout << "  fetched event is valid.\n";
                    //if (tok.is_SD()) std::cout << "  fetched event is SD.\n";
                    std::cout << *tok.get_rep() << std::endl;
                    auto production = current_grammar.find_production_starting_with(tok.as_terminal());
                    
                    if (!production){
                        error_occured = true;
                        std::cerr << "*** Error [v2g_guru_exi::Processor::encode()]: Unexpected EXI-Event\n";
                    } else {
                        std::cout << "  production!\n";
                        std::cout << production->get_lhs().name() <<" : " <<  *(production->get_rhs_rep()) << "\n";
                        auto cur_prod = *production;
                        for(auto it = cur_prod.begin(); it != cur_prod.end(); ++it ){
                            auto rhs_elem = *it;
                            std::cout << *rhs_elem.rep << "\n";
                            if (rhs_elem.is_terminal()){
                                if (!match(rhs_elem.as_terminal())) {
                                    error_occured = true;
                                    std::cerr << "*** Error [v2g_guru_exi::Processor::encode()]: ...\n";
                                    break;
                                }
                            } else if (rhs_elem.is_nonterminal()) {
                                auto nt = rhs_elem.as_nonterminal();
                                auto nt_rhs = current_grammar.right_hand_sides(nt);
                                if (nt_rhs.size()){
                                    auto lookahead = event_stream.peek();
                                    for(size_t i = 0; i < nt_rhs.size(); ++i ){
                                        std::cout << *nt_rhs[i] << std::endl;
                                    }
                                    //cur_prod = Grammar::Production{nt};
                                    exit(0);                                    
                                } else {

                                }

                                //return;
                            } else if (rhs_elem.is_annotation()){

                            }
                        }
                    }
            }// for each event*/
        }
        std::cout << "Processor::encode(): exit.\n";
    }
}