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
    Event::Event(event_rep_t event_rep) : ev_rep{event_rep}, valid{true} {}
    bool Event::is_SD(){
        return is<Ast_node_kind::symbol>(ev_rep) && 
               kind(as_symbol_ref(ev_rep)) == "GrammarTerminal" && 
               name(as_symbol_ref(ev_rep)) == "SD" ;
    }
    std::optional<std::string> Event::get_local_name() const
    {
        return {};
    }
    std::optional<std::string> Event::get_uri() const{
        return string{};
    }
    std::optional<std::string> Event::get_value() const{
        return {};
    }
    std::optional<std::string> Event::get_prefix() const{
        return {};
    }

}