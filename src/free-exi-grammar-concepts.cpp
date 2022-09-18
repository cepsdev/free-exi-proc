
/*
    free-exi-proc - an EXI (= "Efficient XML Interchange") processor
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

    const std::string Grammar::EachLHSContainsExactlyOneNonTerminal::name 
        = "EXIConcept_Grammar_EachLHSContainsExactlyOneNonTerminal";
    const std::string Grammar::NoDanglingLHS::name 
        = "EXIConcept_Grammar_NoDanglingLHS";

    template<> std::pair<bool, Grammar::Error> 
     Grammar::check(Grammar::NoDanglingLHS) {
        bool valid{true};
        Grammar::Error err;
        bool lhs_open = false;
        int ctr = 0;
        foreach_grammar_element_until([&](grammar_elem_t elem) -> bool{
            if (auto lhs = is_lhs(elem,false); lhs){
                if (lhs_open){
                    valid &= ctr != 0;
                } else {lhs_open = true;}
                ctr = 0;
            } else if (auto rhs = is_rhs(elem); rhs){
                ++ctr;
            }
            return valid;
        });
        if (lhs_open && ctr == 0) valid = false;
        return {valid, err};
    }

    template<> std::pair<bool, Grammar::Error> 
     Grammar::check(Grammar::EachLHSContainsExactlyOneNonTerminal) {
        bool valid{true};
        Grammar::Error err;
        foreach_grammar_element_until([&](grammar_elem_t elem) -> bool{
            if (auto lhs = is_lhs(elem,false); lhs){
                lhs = is_lhs(elem,true); // with check
                if (!lhs) {
                    valid = false;
                    err = Grammar::Error::EmptyLefthandside; 
                }
            }
            return true;
        });
        return {valid, err};
    }
}