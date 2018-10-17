cmake_minimum_required(VERSION 3.12)
project(interesting_facts)

set(CMAKE_CXX_STANDARD 17)

if("$ENV{CONDA_ENV}" STREQUAL "")
    message(FATAL_ERROR "")
else()
    set(CONDA_ENV $ENV{CONDA_ENV} CACHE INTERNAL "Copied from environment variable")
    set(CMAKE_PREFIX_PATH ${CONDA_ENV})
endif()

find_package(PythonInterp)
find_package(PythonLibs)
find_package(Boost 1.67 EXACT REQUIRED COMPONENTS system)

add_subdirectory(src)