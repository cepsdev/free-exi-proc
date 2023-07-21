#pragma once
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

#include "ceps_ast.hh"
#include "core/include/state_machine_simulation_core.hpp"


#define model(s)

namespace v2g_guru_exi{
    using namespace ceps::ast;
    using namespace ceps::interpreter;
    using namespace std;

    template<typename T> optional<T> fetch(node_t);

    template<typename T> 
        optional<T> read_value(node_t rep){
            return fetch<T>(rep);
        }
    template<typename T> node_t ast_rep (T entity);

    template<> node_t ast_rep(bool b){
        return mk_int_node(b ? 1 : 0);
    }

}

