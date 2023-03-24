cmake_minimum_required(VERSION 3.24)
project(Low_level_programming3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
add_compile_options(
        -g3
        -O3
)
include(ExternalProject)
EXTERNALPROJECT_ADD(cereal
        GIT_REPOSITORY https://github.com/USCiLab/cereal.git
        PREFIX cereal
        SOURCE_DIR "${CMAKE_BINARY_DIR}/third-party/cereal")
include_directories(${CMAKE_BINARY_DIR}/third-party/cereal/include)

file(GLOB_RECURSE H_FILES_PARSE CONFIGURE_DEPENDS "parse_module/*.h")
file(GLOB_RECURSE CPP_FILES_PARSE CONFIGURE_DEPENDS "parse_module/*.cpp")
file(GLOB_RECURSE CPP_FILES_DB CONFIGURE_DEPENDS "database/*.cpp")
file(GLOB_RECURSE H_FILES_DB CONFIGURE_DEPENDS "database/*.h")
file(GLOB_RECURSE CPP_FILES_COMMON CONFIGURE_DEPENDS "common/*.cxx")
file(GLOB_RECURSE H_FILES_COMMON CONFIGURE_DEPENDS "common/*.hxx")
file(GLOB_RECURSE CPP_FILES_CLIENT CONFIGURE_DEPENDS "client/*.cpp")
file(GLOB_RECURSE H_FILES_CLIENT CONFIGURE_DEPENDS "client/*.h")
file(GLOB_RECURSE H_FILES_SERVER CONFIGURE_DEPENDS "server/*.h")
file(GLOB_RECURSE CPP_FILES_SERVER CONFIGURE_DEPENDS "server/*.cpp")

add_library(PARSE_MODULE STATIC ${H_FILES_PARSE} ${CPP_FILES_PARSE})
add_executable(client client/client.cpp ${CPP_FILES_CLIENT} ${H_FILES_CLIENT} ${CPP_FILES_COMMON} ${H_FILES_COMMON})
target_include_directories(client PUBLIC client)
target_link_libraries(client PARSE_MODULE)
target_link_libraries(client xerces-c PARSE_MODULE)


add_library(DB_MODULE STATIC ${H_FILES_DB} ${CPP_FILES_DB})
add_executable(server server/server.cpp ${CPP_FILES_COMMON} ${H_FILES_COMMON} ${CPP_FILES_SERVER} ${H_FILES_SERVER})
target_include_directories(server PUBLIC server)
target_link_libraries(server DB_MODULE)
target_link_libraries(server xerces-c DB_MODULE)