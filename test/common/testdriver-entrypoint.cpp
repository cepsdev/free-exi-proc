
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
#include "free-exi-terminal.h"
#include "free-exi-proc.h"
#include "v2g-guru-exi-model-adapter.h"
#include "free-exi-terminal-model-adapter.h"

using namespace v2g_guru_exi;

namespace cepsplugin{
    using namespace std;
    using namespace ceps::ast;
    using namespace ceps::interpreter;

    static Ism4ceps_plugin_interface* plugin_master = nullptr;
    static const std::string version_info = "INSERT_NAME_HERE v0.1";
    static constexpr bool print_debug_info{true};
    ceps::ast::node_t plugin_entrypoint_object(ceps::ast::node_callparameters_t params);
    ceps::ast::node_t plugin_entrypoint_operation(ceps::ast::node_callparameters_t params);
}

static  map<string, node_t (*)(Struct&) > ops{ 
        {"match_terminals", [](Struct& s) -> node_t{
            auto& ch{children(s)};
            if (ch.size() < 2) return nullptr;
            auto t1{read_value<Grammar::Terminal>(ch[0])};
            auto t2{read_value<Grammar::Terminal>(ch[1])};
            if(t1 && t2) {
                bool result{};
                return ast_rep(result);   
            }         
            return nullptr;
            }  
        } 
    };

extern void dispatch_method_under_test(ceps::ast::Struct& method,ceps::ast::Struct& result);

/**
 * @brief Entrypoint for exi_obj() calls in the model.
 * 
 * @param params 
 * @return node_t 
 */
node_t cepsplugin::plugin_entrypoint_object(node_callparameters_t params){
    auto args {extract_functioncall_arguments_from_param_block(*params)};
    {
        string sym_name, sym_kind;
	    vector<node_t> arg_s_args; // arg's args
        for(auto a: args)
            if (is_a_symbol_with_arguments(a, sym_name, sym_kind, arg_s_args)){
                auto term{read_value<Grammar::Terminal>(a)};
                if (term)  cout << sym_kind << '\n';
            } else if (is<Ast_node_kind::symbol>(a)){
                auto& sym{as_symbol_ref(a)};
                auto& k{kind(sym)};
                auto& n{name(sym)};
                if(k == "GrammarTerminal")
                {
                    auto op_term{read_value<Grammar::Terminal>(a)};
                    if (!op_term) return mk_undef();
                    return ast_rep(*op_term);
                }
            }
    }
    return mk_undef();
}

ceps::ast::node_t cepsplugin::plugin_entrypoint_operation(ceps::ast::node_callparameters_t params){
    auto data = get_first_child(params);   
    if (!is<Ast_node_kind::structdef>(data)) return mk_undef();
    auto& ceps_struct = *as_struct_ptr(data);

    auto fit{ops.find(name(ceps_struct))};
    if (fit == ops.end()) return mk_undef();
    node_t r{}; 
    try{
        r = fit->second(ceps_struct);
    } catch (std::runtime_error const & e){
        return mk_undef(e.what());    
    }
    if (!r) return mk_undef();
    return r;
}

extern "C" void init_plugin(IUserdefined_function_registry* smc)
{
  v2g_guru_exi::init_model_structures();
  cepsplugin::plugin_master = smc->get_plugin_interface();
  cepsplugin::plugin_master->reg_ceps_phase0plugin("exi_obj", cepsplugin::plugin_entrypoint_object);
  cepsplugin::plugin_master->reg_ceps_phase0plugin("exi_op", cepsplugin::plugin_entrypoint_operation);
}					
				