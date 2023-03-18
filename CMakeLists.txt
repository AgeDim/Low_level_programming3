cmake_minimum_required(VERSION 3.24)
project(Low_level_programming3)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE H_FILES_PARSE CONFIGURE_DEPENDS "parse_module/*.h")
file(GLOB_RECURSE CPP_FILES_PARSE CONFIGURE_DEPENDS "parse_module/*.cpp")


add_library(PARSE_MODULE STATIC ${H_FILES_PARSE} ${CPP_FILES_PARSE})
add_executable(client client/client.cpp)
target_include_directories(client PUBLIC client)
target_link_libraries(client PARSE_MODULE)



add_executable(server server/server.cpp)