cmake_minimum_required(VERSION 3.10)
project(v2g-guru-exi)

add_compile_options(-O  -Wall -MD  -std=c++2a  -fPIC -static -Wno-undef )

IF(NOT( DEFINED ENV{CEPSCORE}))
    MESSAGE(FATAL_ERROR "Could not find ceps core (Environment variable CEPSCORE not set).")
ENDIF()

IF(NOT( DEFINED ENV{MACHINES4CEPS}))
    MESSAGE(FATAL_ERROR "Could not find machines4ceps (Environment variable MACHINES4CEPS not set).")
ENDIF()

IF(NOT( DEFINED ENV{LOG4CEPS}))
    MESSAGE(FATAL_ERROR "Could not find log4ceps (Environment variable LOG4CEPS not set).")
ENDIF()

include_directories($ENV{CEPSCORE}/include)
include_directories($ENV{LOG4CEPS}/include)
include_directories($ENV{MACHINES4CEPS})
include_directories($ENV{MACHINES4CEPS}/core/src_gen/logging)
include_directories(include)
include_directories(../include)
include_directories(include/tests)

link_directories($ENV{CEPSCORE}/bin)

add_library(v2g-guru-exi-plugin SHARED 
           src/ceps-plugin-entrypoint.cpp 
           src/v2g-guru-exi-grammar.cpp
           src/v2g-guru-exi-processor.cpp
           src/v2g-guru-exi-event-stream.cpp
           src/v2g-guru-exi-event.cpp
           src/v2g-guru-exi-ops.cpp
           src/v2g-guru-exi-production.cpp
           src/v2g-guru-exi-terminal.cpp
           src/free-exi-grammar-concepts.cpp
           src/free-exi-proc-stringtable.cpp
           )

target_link_libraries(v2g-guru-exi-plugin cepscore sctp)

add_executable( v2g-guru-exi
                src/exi-standalone.cpp)

target_link_libraries(v2g-guru-exi sctp pthread)
