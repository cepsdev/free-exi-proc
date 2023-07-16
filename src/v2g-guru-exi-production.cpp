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
#include "free-exi-proc.h"

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

bool Grammar::Production::is_generic(int& type) const{
    if (!get_rhs_rep()) return false;
    auto result = false;
    foreach_grammarrep_element_until(
        [&](Grammar::grammar_rep_t elem){
            if(is<Ast_node_kind::structdef>(elem) && name(as_struct_ref(elem))=="add_if_matched") { type = GENERIC_DEFAULT; result = true; return false;}
            if(is<Ast_node_kind::structdef>(elem) && name(as_struct_ref(elem))=="add_if_matched_and_matched_event_code_length_is_not_one") { 
                type=GENERIC_IF_EVCODE_LEN_NOT_ONE; result = true; return false;
            }
            return true;
        }
        ,get_rhs_rep()
    );

    return result;
}

bool Grammar::Production::is_generic() const{
    int type;
    return is_generic(type);
}

optional<Grammar::Production> Grammar::Production::instantiate(Terminal term) const{
    if (!get_rhs_rep()) return {};
    bool success = false;
    Production new_prod{};
    node_t new_rhs_rep = nullptr;
    foreach_grammarrep_element_until(
        [&](Grammar::grammar_rep_t elem){            
            if(is<Ast_node_kind::structdef>(elem) && 
              (name(as_struct_ref(elem))=="add_if_matched" || name(as_struct_ref(elem))=="add_if_matched_and_matched_event_code_length_is_not_one"  ) ) {
                new_rhs_rep = mk_struct("rhs");
                auto& new_rhs_rep_children = children(as_struct_ref(new_rhs_rep));
                foreach_grammarrep_element_until(
                    [&](Grammar::grammar_rep_t e)
                    {
                        if (is<Ast_node_kind::structdef>(e) && name(as_struct_ref(e)) == "do_not_replace") {
                            if (children(as_struct_ref(e)).size())
                                new_rhs_rep_children.push_back( children(as_struct_ref(e))[0]->clone() ); 
                            success = true;                         
                        } else if (term == Terminal{e}){
                            new_rhs_rep_children.push_back(term.get_rep()->clone());
                            success = true;
                        } else {
                            new_rhs_rep_children.push_back(e->clone());
                        }
                        return true;
                    }, elem
                );
                return false;                
            }
            return true;
        }
        ,get_rhs_rep()
    );
    if (!success) {
        delete new_rhs_rep;
        return {};
    }        
    return Production{lhs, new_rhs_rep };
}

optional<Grammar::EventCode> Grammar::Production::get_eventcode(){
    for(auto e : *this){
        if (e.is_eventcode())
            return e.as_eventcode();
    }    
    return {};
}


}