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

std::string Grammar::NonTerminal::name() const{
    return ceps::ast::name(as_symbol_ref(rep));
}

std::optional<Grammar::NonTerminal> Grammar::is_lhs(grammar_elem_t p) const {
    if (!is<Ast_node_kind::structdef>(p)) return {};
    if (name(as_struct_ref(p)) != "lhs") return {};
    for(auto pp : children(as_struct_ref(p))){
        if (!is<Ast_node_kind::symbol>(pp)) continue;
        if (kind(as_symbol_ref(pp))!="GrammarNonterminal") continue;
        return NonTerminal{pp};
    }
    return {};
}

Grammar::lhs_vec_t Grammar::left_hand_sides(){
    lhs_vec_t r{};
    foreach_grammar_element([&](grammar_elem_t p){
        auto res = is_lhs(p);
        if (!res) return;
        r.push_back(*res);
    });
    return r;
}

Grammar::rhs_vec_t Grammar::right_hand_sides(NonTerminal lhs){
    rhs_vec_t r{};
    auto nt{NonTerminal{lhs}};
    bool gather_rhs{};
    foreach_grammar_element([&](grammar_elem_t p){
        auto nonterminal = is_lhs(p);
        if (gather_rhs){
            if (nonterminal){
                 gather_rhs = (*nonterminal == lhs);
                 return;
            }
            if (is<Ast_node_kind::structdef>(p) && name(as_struct_ref(p)) == "rhs" ) 
                r.push_back(p);
            return;
        }
        else if (nonterminal && *nonterminal == lhs) gather_rhs = true;
    });
    return r;
}

bool operator == (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs){
    return lhs.name() == rhs.name();
}

bool operator != (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs){
    return !(lhs == rhs);
}

}