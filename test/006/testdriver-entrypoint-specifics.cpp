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


void dispatch_method_under_test(ceps::ast::Struct& method,ceps::ast::Struct& result){
    using namespace ceps::ast;
    using namespace std;
    for(auto e : children(method)){
        
    }
}
