cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE lib_source_list "src/*.cpp" "src/*.hpp")

add_library(utils ${lib_source_list})

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
