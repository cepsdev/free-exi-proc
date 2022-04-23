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
    Grammar::Production::rhs_elem_t& Grammar::Production::rhs_elem_t::operator= (Grammar::NonTerminal const & rhs){
        if (assoc_it && assoc_it->pos < assoc_it->rep_rhs.size() && rhs.get_rep()){
            assoc_it->rep_rhs[assoc_it->pos] = rep = rhs.get_rep()->clone();
        }
        return *this;
    }    
}