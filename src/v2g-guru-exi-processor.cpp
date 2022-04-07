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

    void Processor::encode(){
        std::cout << "Processor::encode():\n";
        while(grammars.size()){
            auto current_grammar = grammars.top();
            grammars.pop();
            if (!event_stream) break;
            auto tok = event_stream.get_event();
            //std::cout << "  fetched event.\n";
            if (tok){
                //std::cout << "  fetched event is valid.\n";
                //if (tok.is_SD()) std::cout << "  fetched event is SD.\n";
                auto production = current_grammar.find_production_starting_with(tok.as_terminal());
                if (!production){
                    std::cerr << "*** Error [v2g_guru_exi::Processor::encode()]: Unexpected EXI-Event\n";
                } else {
                    //std::cout << production->get_lhs().name() <<" : " <<  *(production->get_rhs_rep()) << "\n";
                }
            }            
        }
        std::cout << "Processor::encode(): exit.\n";
    }
}