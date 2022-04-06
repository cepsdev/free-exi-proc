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
    EventStream::EventStream(event_stream_rep_t event_stream_rep):ev_stream_rep{event_stream_rep} {
        
    }
    Event EventStream::get_event(){
        Event r{};
        if (next_ev_idx >= ev_stream_rep.size()) return r;
        return ev_stream_rep[next_ev_idx++];        
    }
}