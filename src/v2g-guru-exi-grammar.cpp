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

extern std::optional<bool> equality(ceps::ast::Nodebase_ptr lhs, ceps::ast::Nodebase_ptr rhs);

namespace v2g_guru_exi{

bool operator == (Grammar::Terminal const & lhs, Grammar::Terminal const & rhs){
    if (!lhs.valid() || !lhs.valid()) return false;
    if ( is<Ast_node_kind::symbol>(lhs.get_rep()) && is<Ast_node_kind::symbol>(rhs.get_rep()) ){
        if (kind(as_symbol_ref(lhs.get_rep()))!="GrammarTerminal" || kind(as_symbol_ref(lhs.get_rep()))!="GrammarTerminal" ) return false;    
        return name(as_symbol_ref(lhs.get_rep())) == name(as_symbol_ref(rhs.get_rep()));
    } else if (is<Ast_node_kind::func_call>(lhs.get_rep()) && is<Ast_node_kind::func_call>(rhs.get_rep())){
         auto& fl = as_func_call_ref(lhs.get_rep());
         auto& fr = as_func_call_ref(lhs.get_rep());
         auto ftargetl = children(fl)[0];
         auto ftargetr = children(fr)[0];
         if (ftargetl->kind() != ftargetr->kind()) return false;
         if (is<Ast_node_kind::identifier>(ftargetl)){
             auto namel = name(as_id_ref(ftargetl));
             auto namer = name(as_id_ref(ftargetr));
             if (namer != namel) return false;
         } else if(is<Ast_node_kind::symbol>(ftargetl)){
             auto kindl = kind(as_symbol_ref(ftargetl));
             auto kindr = kind(as_symbol_ref(ftargetr));
             if (kindr != kindl) return false;
             auto namel = name(as_symbol_ref(ftargetl));
             auto namer = name(as_symbol_ref(ftargetr));
             if (namel != namer) return false;
         } else return false;
        auto paramsl = &as_call_params_ref( children(fl)[1]);
        auto paramsr = &as_call_params_ref( children(fr)[1]);
        if (children(*paramsr).size() != children(*paramsl).size()) return false;
        if (children(*paramsr).size() == 0) return true;

        if (is<Ast_node_kind::binary_operator>(children(*paramsr)[0]) || is<Ast_node_kind::binary_operator>(children(*paramsl)[0])){
            auto& op = is<Ast_node_kind::binary_operator>(children(*paramsr)[0]) ? as_binop_ref(children(*paramsr)[0]) : as_binop_ref(children(*paramsl)[0]);
            if (op_val(op) != "*") {
                auto eq = equality(children(*paramsr)[0], children(*paramsl)[0]);
                if (eq.has_value()) return *eq;
                return false;
            } else return true;
        } else {
            auto eq = equality(children(*paramsr)[0], children(*paramsl)[0]);
            if (eq.has_value()) return *eq;
            return false;
        } 
    }
    return false;
}

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

vector<Grammar::Production> Grammar::right_hand_sides(NonTerminal lhs){
    rhs_vec_t r{};
    auto nt{NonTerminal{lhs}};
    bool gather_rhs{};
    bool found{};
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
        else if (nonterminal && *nonterminal == lhs) { found = gather_rhs = true;}
    });
    if (!found) return {};
    vector<Grammar::Production> result;
    for(auto rep : r){
        result.push_back(Production{lhs, rep});
    }
    return result;    
}

optional<Grammar::Production> Grammar::find_production_starting_with(Grammar::Terminal term) {
    NonTerminal current_nt{};
    Grammar::Production result{};
    bool found{};

    foreach_grammar_element_until([&](grammar_elem_t elem) -> bool{
        auto new_nt = is_lhs(elem);
        if (new_nt)
            current_nt = *new_nt;
        else if (is<Ast_node_kind::structdef>(elem) && name(as_struct_ref(elem)) == "rhs" ) {
            auto& rhs = as_struct_ref(elem);
            if (!children(rhs).size()) return true;
            if (term == Grammar::Terminal{children(rhs)[0]}){
                found = true;
                result = Grammar::Production{current_nt, elem};
                return false;
            }
        }
        return true;
    });   
    if (found) return result;
    return {};
}


bool operator == (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs){
    return lhs.name() == rhs.name();
}

bool operator != (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs){
    return !(lhs == rhs);
}

}