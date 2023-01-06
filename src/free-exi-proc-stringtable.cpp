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

namespace v2g_guru_exi{
    optional<size_t> StringTable::lookup(string s){
        auto it = v2idx.find(s);
        if (it == v2idx.end()){
            v2idx[s] = next_id++;
            return {};
        }
        return it->second;
    }
    size_t StringTable::bitwidth() const{
        //TODO: Replace with smarter logic (divide and conquer)
        size_t r = 0;
        size_t s = v2idx.size() + 1;
        s >>= 1;
        for (;s; ++r, s >>= 1);
        return r;        
    }

}