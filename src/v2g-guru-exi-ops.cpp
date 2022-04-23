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
    bool Grammar::rename_non_termial(string from , string to){
        if (from.length() == 0 || to.length() == 0) return false;
        bool replaced{};
        foreach_grammar_element([&](grammar_elem_t p){
            auto nonterminal = is_lhs(p);
            if (nonterminal && nonterminal->name() == from){
                nonterminal->set_name(to);replaced = true;
            } else{
                auto prod = is_rhs(p);
                if (prod){
                    for(auto e: *prod){
                        if (!e.is_nonterminal()) continue;
                        auto nt = e.as_nonterminal();
                        if (nt.name() == from){ nt.set_name(to); replaced=true;}                        
                    }
                }
            }
        });
        return replaced;
    }
    bool Grammar::rename_terminal_to_nonterminal(string from , string to){
        if (from.length() == 0 || to.length() == 0) return false;
        bool replaced{};
        foreach_grammar_element([&](grammar_elem_t p){
            auto prod = is_rhs(p);
            if (prod){
                for(auto e: *prod){
                    if (!e.is_terminal()) continue;
                    if (e.as_terminal().name() != from) continue;
                    e = NonTerminal{to};
                    replaced=true;                        
                }
            }
        });
        return replaced;
    }

}