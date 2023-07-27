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
#include <unordered_map>

namespace v2g_guru_exi{

    static void build_term_default(node_t, Grammar::Terminal::qname_t&, Grammar::Terminal::content_t&){

    }

    extern std::unordered_map<std::string, Grammar::Terminal::ev_type_t> ev_type_encoding;
    static std::string term_sym_kind{"GrammarTerminal"};
    
    static std::unordered_map<Grammar::Terminal::ev_type_t, 
                              void (*)(node_t, Grammar::Terminal::qname_t&, Grammar::Terminal::content_t&)> 
     factories_pure_terminal
     {
        {{},build_term_default}

     }; 
    static std::unordered_map<Grammar::Terminal::ev_type_t, 
                              void (*)(node_t, Grammar::Terminal::qname_t&, Grammar::Terminal::content_t&)> 
     factories_parameterized_terminal
     {
        {{},build_term_default}

     }; 
    
    Grammar::Terminal::Terminal(grammar_elem_t rep_arg) {
        //std::cerr << *rep_arg << "\n";
        string err_prefix = "Failed to construct Grammar::Terminal::Terminal: ";
        if (!rep_arg) throw std::invalid_argument{"Terminal(null)"};
        if (is<Ast_node_kind::symbol>(rep_arg)){
            auto& sym{as_symbol_ref(rep_arg)};
            if (kind(sym) != term_sym_kind) throw std::invalid_argument{err_prefix+" unknown kind '"+kind(sym)+"'"};
            auto ev_type_it {ev_type_encoding.find( ceps::ast::name(sym))};
            if (ev_type_it == ev_type_encoding.end()) throw std::invalid_argument{err_prefix+" unknown event type '"+ceps::ast::name(sym)+"'"};
            ev_type = ev_type_it->second;
            auto factory_it{factories_pure_terminal.find(ev_type)};
            if (factory_it == factories_pure_terminal.end()) throw std::runtime_error{err_prefix+" no factory found for '"+ceps::ast::name(sym)+"'"};

        }
         else if (
            is<Ast_node_kind::func_call>(rep_arg) && 
            is<Ast_node_kind::symbol>(func_call_target(as_func_call_ref(rep_arg))) && 
            kind(as_symbol_ref(func_call_target(as_func_call_ref(rep_arg)))) == term_sym_kind  ) 
            rep = rep_arg;
        else rep = nullptr;
    }
}