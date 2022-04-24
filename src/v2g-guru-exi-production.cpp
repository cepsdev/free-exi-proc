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
    Grammar::rhs_vec_t Grammar::Production::empty_vec{};

    Grammar::Production::rhs_elem_t& Grammar::Production::rhs_elem_t::operator= (Grammar::NonTerminal const & rhs){
        if (assoc_it && assoc_it->pos < assoc_it->rep_rhs.size() && rhs.get_rep()){
            assoc_it->rep_rhs[assoc_it->pos] = rep = rhs.get_rep()->clone();
        }
        return *this;
    }    

    Grammar::Production::iterator_t Grammar::Production::begin() {
        return iterator_t{ children(as_struct_ref(rep_rhs)), {} }; 
    }
    
    Grammar::Production::iterator_t Grammar::Production::end() {
        return iterator_t{empty_vec,children(as_struct_ref(rep_rhs)).size()}; 
    }

// rhs_elem_t


    bool Grammar::Production::rhs_elem_t::is_terminal() const {
        return rep !=   nullptr && 
                        (   (is<Ast_node_kind::symbol>(rep) && kind(as_symbol_ref(rep)) == "GrammarTerminal") || 
                            (is<Ast_node_kind::func_call>(rep) && is<Ast_node_kind::symbol>(children(as_func_call_ref(rep))[0]) && kind(as_symbol_ref(children(as_func_call_ref(rep))[0])) == "GrammarTerminal" ) 
                        );
    }
            
    bool Grammar::Production::rhs_elem_t::is_nonterminal() const {
        return rep != nullptr && is<Ast_node_kind::symbol>(rep) && kind(as_symbol_ref(rep)) == "GrammarNonterminal";
    }
            
    bool Grammar::Production::rhs_elem_t::is_action() const {
        return rep != nullptr && is<Ast_node_kind::symbol>(rep) && kind(as_symbol_ref(rep)) == "GrammarAction";
    }
            
    bool Grammar::Production::rhs_elem_t::is_annotation() const {
        return rep != nullptr && !is_terminal() && !is_nonterminal() && !is_action();
    }

    bool Grammar::Production::rhs_elem_t::is_eventcode() const {
        return rep !=   nullptr && 
                        (is<Ast_node_kind::func_call>(rep) && is<Ast_node_kind::identifier>(children(as_func_call_ref(rep))[0]) && name(as_id_ref(children(as_func_call_ref(rep))[0])) == "EventCode" ) 
                        ;
    }

    Grammar::Terminal Grammar::Production::rhs_elem_t::as_terminal() const {
        return {rep};
    }

    Grammar::NonTerminal Grammar::Production::rhs_elem_t::as_nonterminal() const {
        return {rep};
    }
                            
    Grammar::EventCode Grammar::Production::rhs_elem_t::as_eventcode() const {
        return {rep};
    }

    Grammar::Action Grammar::Production::rhs_elem_t::as_action() const {
        return {rep};
    }

}