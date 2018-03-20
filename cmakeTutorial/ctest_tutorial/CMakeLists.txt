cmake_minimum_required(VERSION 3.9)
project(ctest_tutorial)

set(CMAKE_CXX_STANDARD 17)


include(CTest)
# Enable unit testing if BUILD_TESTING option is ON
if(BUILD_TESTING)
    enable_testing()  # Allows you to run "make test"
endif()

add_executable(ctest_tutorial templates.cpp)