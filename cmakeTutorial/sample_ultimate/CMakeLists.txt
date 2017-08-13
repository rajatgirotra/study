cmake_minimum_required(VERSION 3.5)


# set prefix path
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /home/rajatgirotra/tools/miniconda2/envs/shriram)
# set module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(sample_ultimate VERSION 1.0.0 LANGUAGES C CXX)
# set(CMAKE_CXX_STANDARD 14)

option(UNITTESTS "Build unit tests." ON)
message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")
message(STATUS "UNITTESTS: ${UNITTESTS}")

# Check Compiler has support needed
include(CompilerCheck)

# include CTest package
include (CTest)

# set release type - default is dev
set(RELEASE_TYPE dev)
configure_file(${CMAKE_MODULE_PATH}/config.hpp.in internal/config.hpp)

find_package(Boost REQUIRED COMPONENTS regex system signals program_options filesystem python)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "${PROJECT_NAME} needs BOOST to build. No BOOST installation found.")
else()
    add_library(boost_regex SHARED IMPORTED)
    set_target_properties(boost_regex PROPERTIES IMPORTED_LOCATION ${Boost_REGEX_LIBRARY})

    add_library(boost_system SHARED IMPORTED)
    set_target_properties(boost_system PROPERTIES IMPORTED_LOCATION ${Boost_SYSTEM_LIBRARY})

    add_library(boost_signals SHARED IMPORTED)
    set_target_properties(boost_signals PROPERTIES IMPORTED_LOCATION ${Boost_SIGNALS_LIBRARY})

    add_library(boost_program_options SHARED IMPORTED)
    set_target_properties(boost_program_options PROPERTIES IMPORTED_LOCATION ${Boost_PROGRAM_OPTIONS_LIBRARY})

    add_library(boost_filesystem SHARED IMPORTED)
    set_target_properties(boost_filesystem PROPERTIES IMPORTED_LOCATION ${Boost_FILESYSTEM_LIBRARY})

    add_library(boost_python SHARED IMPORTED)
    set_target_properties(boost_python PROPERTIES IMPORTED_LOCATION ${Boost_PYTHON_LIBRARY})
endif()

if(UNITTESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    if(NOT GTEST_FOUND)
        message(FATAL_ERROR "${PROJECT_NAME} needs GoogleTest/GoogleMock to build. No GoogleTest/GoogleMock installation found.")
    endif()
    get_filename_component(GTEST_ROOT_DIR ${GTEST_INCLUDE_DIRS} DIRECTORY)
    message(STATUS "GTest: ${GTEST_ROOT_DIR}")
endif()

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory("src/common")
add_subdirectory("src/main")