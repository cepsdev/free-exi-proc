
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

#include "ceps_ast.hh"
#include "core/include/state_machine_simulation_core.hpp"


#include "v2g-guru-exi.h"

namespace v2g_guru_exi{
    static Ism4ceps_plugin_interface* plugin_master = nullptr;
    static const std::string version_info = "v2g-guru-exi v0.1";
    static constexpr bool print_debug_info{true};
    static Processor exi_processor; 
}


namespace cepsplugin{
    static Ism4ceps_plugin_interface* plugin_master = nullptr;
    static const std::string version_info = "INSERT_NAME_HERE v0.1";
    static constexpr bool print_debug_info{true};
    ceps::ast::node_t plugin_entrypoint(ceps::ast::node_callparameters_t params);
}

extern void dispatch_method_under_test(ceps::ast::Struct& method,ceps::ast::Struct& result);

ceps::ast::node_t cepsplugin::plugin_entrypoint(ceps::ast::node_callparameters_t params){
    using namespace std;
    using namespace ceps::ast;
    using namespace ceps::interpreter;

    auto data = get_first_child(params);    
    if (!is<Ast_node_kind::structdef>(data)) return nullptr;
    auto& ceps_struct = *as_struct_ptr(data);
    //cout << ceps_struct << '\n';
    auto result = mk_struct("result");
    dispatch_method_under_test(ceps_struct,*result);

    //for(auto e : children(ceps_struct)){
    //}
    //children(*result).push_back(mk_int_node(42));
    return result;
}

extern "C" void init_plugin(IUserdefined_function_registry* smc)
{
  cepsplugin::plugin_master = smc->get_plugin_interface();
  cepsplugin::plugin_master->reg_ceps_phase0plugin("exi_proc", cepsplugin::plugin_entrypoint);
}					
				