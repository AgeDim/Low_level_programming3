cmake_minimum_required(VERSION 3.24)
project(Low_level_programming3)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE H_FILES_PARSE CONFIGURE_DEPENDS "parse_module/*.h")
file(GLOB_RECURSE CPP_FILES_PARSE CONFIGURE_DEPENDS "parse_module/*.cpp")
file(GLOB_RECURSE CPP_FILES_COMMON CONFIGURE_DEPENDS "common/*.cxx")
file(GLOB_RECURSE H_FILES_COMMON CONFIGURE_DEPENDS "common/*.hxx")
file(GLOB_RECURSE CPP_FILES_CLIENT CONFIGURE_DEPENDS "client/*.cpp")
file(GLOB_RECURSE H_FILES_CLIENT CONFIGURE_DEPENDS "client/*.h")

add_library(PARSE_MODULE STATIC ${H_FILES_PARSE} ${CPP_FILES_PARSE})
add_executable(client client/client.cpp ${CPP_FILES_CLIENT} ${H_FILES_CLIENT} ${CPP_FILES_COMMON} ${H_FILES_COMMON})
target_include_directories(client PUBLIC client)
target_link_libraries(client PARSE_MODULE)
target_link_libraries(client xerces-c PARSE_MODULE)



add_executable(server server/server.cpp ${CPP_FILES_COMMON} ${H_FILES_COMMON})
target_link_libraries(server xerces-c)