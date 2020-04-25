cmake_minimum_required(VERSION 3.16)

project(CPP_NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(auto_with_brace_initialization auto_with_brace_initialization.cpp)
add_subdirectory(RValueReferences)
add_subdirectory(chrono)
add_subdirectory(sfinae_and_enable_if)
add_subdirectory(iterators)
add_subdirectory(hashes_maps_sets)
add_subdirectory(random)
add_subdirectory(constexpr)