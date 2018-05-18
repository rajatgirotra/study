cmake_minimum_required(VERSION 3.10)

project(boost_python_study VERSION 1.0.0 LANGUAGES C CXX)

# set cmake_prefix_path
if ("$ENV{CONDA_ENV}" STREQUAL "")
    message(FATAL_ERROR "Environment variable CONDA_ENV not found")
else()
    set(CONDA_ENV $ENV{CONDA_ENV} CACHE INTERNAL "Copied from environment variable")
    set(CMAKE_PREFIX_PATH "${CONDA_ENV}")
endif()

# find python and python libs
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Boost 1.67 EXACT REQUIRED COMPONENTS python27)

add_compile_options("$<$<CONFIG:Debug>:-gdwarf-4>" "$<$<CONFIG:Release>:>")

add_subdirectory(src)
