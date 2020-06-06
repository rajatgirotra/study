cmake_minimum_required(VERSION 3.10)
project(c_api)

set(CMAKE_CXX_STANDARD 17)

# Make sure CONDA_ENV is defined.
if("$ENV{CONDA_ENV}" STREQUAL "")
    message(FATAL_ERROR "environment variable CONDA_ENV not set")
else()
    set(CONDA_ENV "$ENV{CONDA_ENV}" CACHE INTERNAL "Copied from environment variable")
    set(CMAKE_PREFIX_PATH ${CONDA_ENV})
endif()


# find boost
find_package(Boost 1.67 EXACT REQUIRED)

# find python interp
find_package(PythonInterp)
if(NOT PYTHONINTERP_FOUND)
    message(FATAL_ERROR "No Python installation found. Cannot proceed")
endif()

# find pythonlibs
find_package(PythonLibs)
if(NOT PYTHONLIBS_FOUND)
    message(FATAL_ERROR "No Python Lib. Cannot proceed")
endif()

add_compile_options("$<$<CONFIG:Debug>:-gdwarf-4>"
        "$<$<CONFIG:Release>:>")

add_subdirectory(src)