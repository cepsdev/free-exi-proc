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

    Grammar::sorted_vec_of_unique_nonterminals_t Grammar::get_lhs_nonterminals() const{
        sorted_vec_of_unique_nonterminals_t r{};
        foreach_grammar_element([&](grammar_elem_t p){
            auto nonterminal = is_lhs(p);
            if (nonterminal) 
                r.push_back(*nonterminal);
        });
        sort(r.begin(), r.end());
        auto last = unique(r.begin(), r.end());
        r.erase(last, r.end());
        return r;
    }

    Grammar::sorted_vec_of_unique_nonterminals_t Grammar::get_all_nonterminals() const{
        sorted_vec_of_unique_nonterminals_t r{};
        foreach_grammar_element([&](grammar_elem_t p){
            auto nonterminal = is_lhs(p);
            if (nonterminal) 
                r.push_back(*nonterminal);
        });
        sort(r.begin(), r.end());
        auto last = unique(r.begin(), r.end());
        r.erase(last, r.end());
        return r;
    }

    Grammar::sorted_vec_of_unique_nonterminals_t Grammar::confliciting_nonterminals(Grammar const & g) const
    {
        sorted_vec_of_unique_nonterminals_t r{};
        auto lhs_nonterminals = get_lhs_nonterminals();
        auto rhs_nonterminals = g.get_lhs_nonterminals();
        if (lhs_nonterminals.size() == 0 || rhs_nonterminals.size() == 0) return r;
        for (auto nt : lhs_nonterminals)
            if (binary_search(rhs_nonterminals.begin(), rhs_nonterminals.end(),nt))
                r.push_back(nt);
        return r;
    }

    Grammar::vec_pairs_of_nonterminals_t Grammar::resolve_conflicting_nonterminals(Grammar const & g) const{
        auto nts_in_conflict = confliciting_nonterminals(g);
        auto lhs_all_nts = get_lhs_nonterminals();
        auto rhs_all_nts = g.get_lhs_nonterminals();
        vec_pairs_of_nonterminals_t  r;

        for(auto nt_in_conflict : nts_in_conflict){
            for(int i = 1; ; ++i){
                auto new_nt_name = nt_in_conflict.name() + "_" + to_string(i);
                auto new_nt{new_nt_name};
                if (binary_search(lhs_all_nts.begin(), lhs_all_nts.end(),new_nt)) continue;
                if (binary_search(rhs_all_nts.begin(), rhs_all_nts.end(),new_nt)) continue;
                r.push_back(make_pair(nt_in_conflict,new_nt));
                break;
            }
        }
        return r;
    }
}