cmake_minimum_required(VERSION 3.10)
project(interprocess VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

if("$ENV{CONDA_ENV}" STREQUAL "")
    message(FATAL_ERROR "Envrionment Variable COND_ENV not set")
else()
    set(CONDA_ENV $ENV{CONDA_ENV} CACHE INTERNAL "Copied from environment variable")
    set(CMAKE_PREFIX_PATH "${CONDA_ENV}")
endif()


find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Boost 1.67 EXACT REQUIRED COMPONENTS date_time)

add_subdirectory(src)
