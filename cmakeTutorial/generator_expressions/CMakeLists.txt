cmake_minimum_required(VERSION 3.5)

project(DUMMY VERSION 1.0.0 LANGUAGES C CXX)

message(STATUS "CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")
message(STATUS "CONFIG ${CMAKE_BUILD_TYPE}")

add_definitions(-std=c++14)

#add_compile_options($<$<CONFIG:DEBUG>:-g -O0>)
#add_compile_options($<$<CONFIG:DEBUG>:-O3>)
add_executable(main main.cpp)
target_compile_options(main PRIVATE $<$<CONFIG:DEBUG>:-g -O3> $<$<CONFIG:RELEASE>:-O3>)


