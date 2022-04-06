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


#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <chrono>
#include <sstream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <future>
#include <netinet/sctp.h> 

#include "v2g-guru-exi.h"

namespace v2g_guru_exi{
    static Ism4ceps_plugin_interface* plugin_master = nullptr;
    static const std::string version_info = "v2g-guru-exi v0.1";
    static constexpr bool print_debug_info{true};
    static Processor exi_processor; 
    ceps::ast::node_t plugin_entrypoint_add_start_grammar(ceps::ast::node_callparameters_t params);
    ceps::ast::node_t plugin_entrypoint_encode (ceps::ast::node_callparameters_t params);
}

ceps::ast::node_t v2g_guru_exi::plugin_entrypoint_add_start_grammar(ceps::ast::node_callparameters_t params){
    auto data = get_first_child(params);
    
    if (!is<Ast_node_kind::structdef>(data)) return nullptr;
    auto& ceps_struct = *as_struct_ptr(data);
    if("Grammar" != name(ceps_struct)) return nullptr;
    Grammar g{data};

    if(v2g_guru_exi::print_debug_info){
        std::cout << "plugin_entrypoint_add_start_grammar(G) where G = { \n";
        auto v_lhs = g.left_hand_sides();
        for(auto p : v_lhs) {
            std::cout << "  " << p.name() << ":\n";
            auto v_rhs = g.right_hand_sides(p);
            for(auto pp : v_rhs)
                std::cout << "    " << *pp << "\n";
        }
        std::cout << "\n}\n"; 
    }
    
    exi_processor.set_start_grammar(g);
    
    return nullptr;
}

ceps::ast::node_t v2g_guru_exi::plugin_entrypoint_encode (ceps::ast::node_callparameters_t params){
    auto data = get_first_child(params);
    auto result = mk_struct("encoding");
    
    if (!is<Ast_node_kind::structdef>(data)) return result;
    auto& ceps_struct = *as_struct_ptr(data);
    if("events" != name(ceps_struct)) return result;

    exi_processor.set_event_stream(EventStream{children(ceps_struct)});
    exi_processor.encode();
    return result;
}

extern "C" void init_plugin(IUserdefined_function_registry* smc)
{
  v2g_guru_exi::plugin_master = smc->get_plugin_interface();
  v2g_guru_exi::plugin_master->reg_ceps_plugin("exi_processor_add_start_grammar", v2g_guru_exi::plugin_entrypoint_add_start_grammar);
  v2g_guru_exi::plugin_master->reg_ceps_plugin("exi_processor_encode", v2g_guru_exi::plugin_entrypoint_encode);

  if(v2g_guru_exi::print_debug_info) std::cout << v2g_guru_exi::version_info << " registered.\n";
}

