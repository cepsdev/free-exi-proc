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

Grammar::Terminal Event::as_terminal() const { return Grammar::Terminal{ev_rep}; }
bool operator < (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs){
    return lhs.name() < rhs.name();
}

bool operator == (Grammar::Terminal const & lhs, Grammar::Terminal const & rhs){
    if (!lhs.valid() || !rhs.valid()) return false;
    if ( is<Ast_node_kind::symbol>(lhs.get_rep()) && is<Ast_node_kind::symbol>(rhs.get_rep()) ){
        if (kind(as_symbol_ref(lhs.get_rep()))!="GrammarTerminal" || kind(as_symbol_ref(rhs.get_rep()))!="GrammarTerminal" ) return false;    
        return name(as_symbol_ref(lhs.get_rep())) == name(as_symbol_ref(rhs.get_rep()));
    } else if (is<Ast_node_kind::func_call>(lhs.get_rep()) && is<Ast_node_kind::func_call>(rhs.get_rep())){
         auto& fl = as_func_call_ref(lhs.get_rep());
         auto& fr = as_func_call_ref(rhs.get_rep());
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
        
        if (is<Ast_node_kind::binary_operator>(children(*paramsr)[0]) && is<Ast_node_kind::binary_operator>(children(*paramsl)[0])){
            if ( op_val(as_binop_ref(children(*paramsl)[0])) == "*" || op_val(as_binop_ref(children(*paramsr)[0])) == "*" ) return true;
            if ( op_val(as_binop_ref(children(*paramsl)[0])) != op_val(as_binop_ref(children(*paramsr)[0])) ) return false;
            auto lhsl = as_binop_ref(children(*paramsl)[0]).left();
            auto lhsr = as_binop_ref(children(*paramsr)[0]).left();
            if (lhsl->kind() != lhsr->kind()) return false;
            if ( is<Ast_node_kind::identifier>(lhsl) ) return name(as_id_ref(lhsl)) == name(as_id_ref(lhsr));
            if ( is<Ast_node_kind::string_literal>(lhsl) ) return value(as_string_ref(lhsl)) == value(as_string_ref(lhsr));
            if ( is<Ast_node_kind::symbol>(lhsl) ) return (name(as_symbol_ref(lhsl)) == name(as_symbol_ref(lhsr))) && (kind(as_symbol_ref(lhsl)) == kind(as_symbol_ref(lhsr)));

            return false;
        }
        else if (is<Ast_node_kind::binary_operator>(children(*paramsr)[0]) || is<Ast_node_kind::binary_operator>(children(*paramsl)[0])){
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

string Grammar::Terminal::as_str() const{
    if (!rep) return "";
    stringstream ss;
    ss << *rep; return ss.str();
}

void Grammar::Terminal::set_name(string new_name){
    if(!rep) return;
}

string Grammar::Terminal::name() const {
    if(!rep) return "";
    stringstream ss;
    if(is<Ast_node_kind::symbol>(get_rep())){
        ss << ceps::ast::name(as_symbol_ref(get_rep()));
    } else if (is<Ast_node_kind::func_call>(get_rep()) && 
               is<Ast_node_kind::symbol>(func_call_target(as_func_call_ref(get_rep()))) && 
               kind(as_symbol_ref(func_call_target(as_func_call_ref(get_rep())))) == "GrammarTerminal"){
    
        ss << ceps::ast::name(as_symbol_ref(func_call_target(as_func_call_ref(get_rep())))) << "(";
        auto& f = as_func_call_ref(get_rep());
        auto params = &as_call_params_ref( children(f)[1]);
        if (children(*params).size()){
            auto print_expr = [&](node_t e){
                if (is<Ast_node_kind::identifier>(e)) ss << ceps::ast::name(as_id_ref(e));
                else if (is<Ast_node_kind::string_literal>(e)) ss << "\"" <<  value(as_string_ref(e)) << "\"";
                else if (is<Ast_node_kind::int_literal>(e)) ss << value(as_int_ref(e));
            };
            if (is<Ast_node_kind::binary_operator>(children(*params)[0])){
                auto& op = as_binop_ref(children(*params)[0]);
                print_expr(op.left());
                if (op_val(op) == "*") { 
                    ss << " " << op_val(op) << " "; 
                    print_expr(op.right());
                }
            } else print_expr(children(*params)[0]);
        }
        ss << ")";
    }
    return ss.str();
}

// Grammar::NonTerminal

Grammar::NonTerminal::NonTerminal (std::string nm){
    rep = ceps::ast::mk_symbol(nm, "GrammarNonterminal");
}

std::string Grammar::NonTerminal::name() const{
    return ceps::ast::name(as_symbol_ref(rep));
}

// Grammar

Grammar::Grammar(NonTerminal nt,Grammar const & g){
    //grammar_rep = mk_struct("Grammar");
    *this = g;
    auto v = left_hand_sides();
    if (!v.size() || !nt.get_rep()) return;
    auto& vv = children(as_struct_ref(grammar_rep));
    auto new_lhs = mk_struct("lhs");
    children(*new_lhs).push_back(nt.get_rep()->clone());   
    vv.insert(vv.begin(),v[0].get_rep()->clone());
    vv.insert(vv.begin(), new_lhs);
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

std::optional<Grammar::Production> Grammar::is_rhs(grammar_elem_t p) const{
    if (!is<Ast_node_kind::structdef>(p)) return {};
    if (name(as_struct_ref(p)) != "rhs") return {};
    return Production{NonTerminal{},p};
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
        if (new_nt.has_value())
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

void Grammar::insert(Grammar::Production prod) {

    bool in_scope = false;
    size_t insert_pos = 0;
    auto cur_ev = prod.get_eventcode();
    vector<int> positions;
    int lhs_pos = 0;

    foreach_grammar_element_until([&](grammar_elem_t elem) -> bool{
        if (is<Ast_node_kind::structdef>(elem) && name(as_struct_ref(elem)) == "lhs" ) {
            lhs_pos = insert_pos;
            ++insert_pos;
            auto& lhs = as_struct_ref(elem);
            if (!children(lhs).size()) return true;
            if (prod.get_lhs() == NonTerminal{children(lhs)[0]}) in_scope = true;
            else in_scope = false;            
            return true;
        } else if (is<Ast_node_kind::structdef>(elem) && name(as_struct_ref(elem)) == "rhs" && in_scope){
            positions.push_back(insert_pos);
        }
        ++insert_pos;
        return true;
    });
    if (positions.size()){
        auto to_insert = prod.get_rhs_rep()->clone();
        auto& v = children(as_struct_ref(grammar_rep));
        if (!cur_ev) insert_pos = 0;
        else {
            insert_pos = positions.size() - 1;
            for(size_t i = 0; i < positions.size(); ++i){
                auto cur_prod = Production{prod.get_lhs(), v[positions[i]] };
                auto ev = cur_prod.get_eventcode();
                if (!ev) continue;
                if (*cur_ev <= *ev) {
                    if (i > 0) insert_pos = i - 1;
                    else insert_pos = 0;
                    break;
                }
            }            
        }

        for(size_t i = insert_pos; i < positions.size(); ++i)
             Production{prod.get_lhs(), v[positions[i]] }.incr_ev_pos(1,0);
        v.insert(v.begin() + positions[insert_pos] , to_insert);        
    }
}

void Grammar::Production::incr_ev_pos(int delta, int pos){
    for(auto e : *this){
        if (!e.is_eventcode()) continue;
        //std::cout << *e.rep << " --- \n";
        auto ev = e.as_eventcode();
        if (ev.dim < pos) continue;
        value(as_int_ref(ev.get_code_rep()[pos])) += delta;
        break;
    }
}

bool operator <= (Grammar::EventCode lhs, Grammar::EventCode rhs){
    auto n = min(lhs.dim, rhs.dim);
    for(int i = 0; i < n; ++i)
     if (lhs.code[i] > rhs.code[i]) return false;
    if (lhs.dim > rhs.dim) return false;
    return true;
} 

// NonTerminal

void Grammar::NonTerminal::set_name(string new_name){
    if (rep == nullptr) return;
    ceps::ast::name(as_symbol_ref(rep)) = new_name;
}


bool operator == (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs){
    return lhs.name() == rhs.name();
}

bool operator != (Grammar::NonTerminal const & lhs, Grammar::NonTerminal const & rhs){
    return !(lhs == rhs);
}

/// Grammar

ostream& operator << (ostream& os, Grammar::Terminal term){
    if (!term.get_rep()) return os;
    if(is<Ast_node_kind::symbol>(term.get_rep()) && kind(as_symbol_ref(term.get_rep())) == "GrammarTerminal"){
        os << name(as_symbol_ref(term.get_rep()));
    } else if (is<Ast_node_kind::func_call>(term.get_rep()) && 
               is<Ast_node_kind::symbol>(func_call_target(as_func_call_ref(term.get_rep()))) && 
               kind(as_symbol_ref(func_call_target(as_func_call_ref(term.get_rep())))) == "GrammarTerminal"){
    
        os << name(as_symbol_ref(func_call_target(as_func_call_ref(term.get_rep())))) << "(";
        auto& f = as_func_call_ref(term.get_rep());
        auto params = &as_call_params_ref( children(f)[1]);
        if (children(*params).size()){
            auto print_expr = [&](node_t e){
                if (is<Ast_node_kind::identifier>(e)) os << name(as_id_ref(e));
                else if (is<Ast_node_kind::string_literal>(e)) os << "\"" <<  value(as_string_ref(e)) << "\"";
                else if (is<Ast_node_kind::int_literal>(e)) os << value(as_int_ref(e));
            };
            if (is<Ast_node_kind::binary_operator>(children(*params)[0])){
                auto& op = as_binop_ref(children(*params)[0]);
                print_expr(op.left());
                os << " " << op_val(op) << " "; 
                print_expr(op.right());
            } else print_expr(children(*params)[0]);
        }
        os << ")";
    }
    return os;
}
 
ostream& operator << (ostream& os, Grammar::NonTerminal nt ){
    os << nt.name();
    return os;
}

ostream& operator << (ostream& os, Grammar g){
    os << "Grammar ";
    if (g.has_global_id()) os << "id = '"<< g.global_id() << "'"; 
    os << ":\n\n";
    for (auto lhs : g.left_hand_sides()){
        os << "    " << lhs << " ==>\n";
        auto prods = g.right_hand_sides(lhs);
        for (auto prod : prods){
            os << "        ";
            for (auto e: prod){
                if (e.is_eventcode()) {
                    auto ev = e.as_eventcode();
                    os << ev << "   ";
                } else if (e.is_nonterminal()){
                     auto nt = e.as_nonterminal();
                     os << nt << "   ";
                } else if (e.is_terminal()){
                    os << e.as_terminal()<< "   ";
                }
            }
            os << "\n";
        }
    }
    os << "\n\n";
    return os; 
}


ostream& operator << (ostream& os, Grammar::Production  p){
    os << p.get_lhs().name() << ": " ;

    for (auto e: p){
                if (e.is_eventcode()) {
                    auto ev = e.as_eventcode();
                    os << ev << "   ";
                } else if (e.is_nonterminal()){
                     auto nt = e.as_nonterminal();
                     os << nt << "   ";
                } else if (e.is_terminal()){
                    os << e.as_terminal()<< "   ";
                }
    }
    os << "\n";

    return os;
}

GenericGrammar::GenericGrammar(Grammar::grammar_elem_t generic_raw){
    if (generic_raw == nullptr) return;
    if (!is<Ast_node_kind::structdef>(generic_raw)) return;
    foreach_grammarrep_element_until  ([&](Grammar::grammar_rep_t elem){
        if(!is<Ast_node_kind::structdef>(elem)) return true;
        auto& data = as_struct_ref(elem);
        if (name(data) == "Pattern") {
            auto& v = children(data);
            if (v.size() == 0) return true;
            pattern = v[0];
        }
        if (name(data) == "Grammar") g = Grammar{elem};
        return true;
    },generic_raw);
}

string GenericGrammar::pattern_to_str(){
    if (pattern_str_cache_valid) return pattern_str_cache;
    pattern_str_cache_valid = true;
    if (pattern == nullptr) pattern_str_cache = "";
    stringstream ss;
    ss << *pattern;
    pattern_str_cache = ss.str();
    return pattern_str_cache;
}

    ostream& operator << (ostream& os, Grammar::EventCode const & ev){
        if (!ev.valid()) os << "Invalid EventCode";
        else {
            os << "EventCode(";
            for(size_t i = 0; i < (size_t)ev.dim; ++i){
                os << ev.code[i];
                if (i+1 < (size_t)ev.dim) os << ",";
            }
            os << ")";
        } 
        return os;   
    }

    void Grammar::append(Grammar const & g){
        if (!g.get_rep()) return;
        if (!get_rep())
            grammar_rep = mk_struct("Grammar");
        auto & rv = children(as_struct_ref(g.get_rep()));        
        copy(rv.begin(), rv.end(), back_inserter(children(as_struct_ref(get_rep()))));            
    }
}