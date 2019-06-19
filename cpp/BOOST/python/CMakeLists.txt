cmake_minimum_required(VERSION 3.10)

project(boost_python_study)

set(CMAKE_CXX_STANDARD 17)

# find python and python libs
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Boost 1.68 EXACT REQUIRED COMPONENTS python37)

add_compile_options("$<$<CONFIG:Debug>:-gdwarf-4>" "$<$<CONFIG:Release>:>")

add_subdirectory(src)
add_subdirectory(delete)
