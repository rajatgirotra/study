cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(ConanTest LANGUAGES C CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(md5_test md5.cpp)
target_link_libraries(md5_test ${CONAN_LIBS})
target_compile_options(md5_test PUBLIC -std=c++17)
