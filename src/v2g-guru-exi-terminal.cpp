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

namespace v2g_guru_exi{


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

using namespace std;
optional<Grammar::Terminal::content_t> Grammar::Terminal::get_content() const{
    if (!valid()) return {};
    if (!get_rep()) return {};
    
    #if 0
    auto nm = name().substr(0,2);
    if (nm == "EE" || nm == "SC" || nm == "SD" || nm == "ED" ) return {};
    Grammar::Terminal::content_t r{};

    if (nm == "SE" || nm == "AT" || nm == "NS"){
		string func_id;string fkind;string sym_name;
	    node_t ftarget;vector<node_t> args;         

        if (is_a_funccall(	get_rep(),func_id,fkind,sym_name,ftarget,args)){
            if (args.size()){
                if (is<Ast_node_kind::string_literal>(args[0])) 
                    r.local_name = value(as_string_ref(args[0]));
                if (is<Ast_node_kind::binary_operator>(args[0])){
                    auto& op = as_binop_ref(args[0]);
                    if(is<Ast_node_kind::identifier>(op.left())) 
                        r.local_name = ceps::ast::name(as_id_ref(op.left()));
                    if(is<Ast_node_kind::string_literal>(op.right()))
                        r.value = value(as_string_ref(op.right())); 
                }
                                        
                for(auto i = 1; i != args.size(); ++i){
		            string func_id;string fkind;string sym_name;
	                node_t ftarget;vector<node_t> args2;         

                    if (is_a_funccall(	args[i],func_id,fkind,sym_name,ftarget,args2)){
                        if(sym_name == "uri" && args2.size()){
                            r.uri = 
                             is<Ast_node_kind::string_literal>(args2[0]) ? value(as_string_ref(args2[0])): "";
                        } else if(sym_name == "prefix" && args2.size()){
                            r.prefix = 
                             is<Ast_node_kind::string_literal>(args2[0]) ? value(as_string_ref(args2[0])): "";
                        }
                    }
                }
            }
        }
    } else if (nm == "CH"){
		string func_id;string fkind;string sym_name;
	    node_t ftarget;vector<node_t> args;
        if (is_a_funccall(	get_rep(),func_id,fkind,sym_name,ftarget,args)){
            if (args.size()){
                if (is<Ast_node_kind::string_literal>(args[0])) 
                    r.value = value(as_string_ref(args[0]));
                for(auto i = 1; i != args.size(); ++i){
		            string func_id;string fkind;string sym_name;
	                node_t ftarget;vector<node_t> args2;

                    cout << *args[i] << "\n\n";         

                    if (is_a_funccall(	args[i],func_id,fkind,sym_name,ftarget,args2)){
                        if( (func_id == "inherited_uri" || sym_name == "inherited_uri" ) && args2.size()){
                            r.inherited_uri = 
                             is<Ast_node_kind::string_literal>(args2[0]) ? value(as_string_ref(args2[0])): "";
                        } else if( (func_id == "inherited_name" || sym_name == "inherited_name" ) && args2.size()){
                            r.inherited_name = 
                             is<Ast_node_kind::string_literal>(args2[0]) ? value(as_string_ref(args2[0])): "";
                        }
                    }
                }

            }
        }
    }
    #endif
    return {};
} 



}








