cmake_minimum_required(VERSION 3.16)

project(cpp_study DESCRIPTION "cpp starter project makefile" LANGUAGES C CXX)

# conan setup for cmake generator
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

# conan setup for cmake_find_package generator
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CONAN_CMAKE_SILENT_OUTPUT True)

include(cmake/StandardProjectSettings.cmake)

# create an interface target. and attach project wide compiler warnings to it.
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# create an interface target. we can attach cmake properties to this library which will apply globally to our build.
add_library(project_options INTERFACE)
# cmake now has its own dataset of compilers names, versions and the features that are supported by those compiler versions
# CMAKE_CXX_KNOWN_FEATURES is a list of all c++ features known to cmake. CMAKE_CXX_COMPILE_FEATURES is a subset of CMAKE_CXX_KNOWN_FEATURES
# which can be used to turn off/on certain flags. Here we use one such feature to turn on C++17 flag
target_compile_features(project_options INTERFACE cxx_std_17)

# set compile/link options
include(cmake/CompilerFlags.cmake)
set_project_flags(project_options)

# sanitizer options if supported by the compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# enable verbose build
set(CMAKE_VERBOSE_MAKEFILE ON)

# Python3
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
message(STATUS "using ${Python3_INTERPRETER_ID}, ${Python3_VERSION} executable: ${Python3_EXECUTABLE},"
        " include-path: ${Python3_INCLUDE_DIRS},"
        " libs: ${Python3_LIBRARIES}")

# Boost
find_package(Boost 1.76.0 EXACT REQUIRED QUIET COMPONENTS system date_time python)
message(STATUS "using Boost ${Boost_VERSION_STRING}, include-path: ${Boost_INCLUDE_DIRS},"
        " libs - ${Boost_LIBRARIES}")

# Google Benchmark
find_package(benchmark 1.5.3 EXACT REQUIRED QUIET COMPONENTS)
message(STATUS "using Google Benchmark ${}, include-path: ${benchmark_INCLUDE_DIRS},"
        " libs - ${benchmark_LIBS}")

# Find SQLite3
find_package(SQLite3 3.35.5 EXACT REQUIRED QUIET)
message(STATUS "using sqlite3 ${SQLite3_VERSION}, include-path: ${SQLite3_INCLUDE_DIRS},"
        " libs - ${SQLite3_LIBRARIES}")

# find valgrind program
find_program(VALGRIND_EXECUTABLE NAMES valgrind REQUIRED)
message(STATUS "using valgrind: ${VALGRIND_EXECUTABLE}")

# Find Google-protobuf
#set(ENV{Protobuf_SRC_ROOT_FOLDER} ${DEVTOOLS_DIR})
#find_package(Protobuf REQUIRED QUIET)
#message(STATUS "using google-protobuf ${Protobuf_VERSION}, include-path: ${Protobuf_INCLUDE_DIRS},"
#        " libs - ${Protobuf_LIBRARIES}, protoc: ${Protobuf_PROTOC_EXECUTABLE}")


# enable/disable test builds and running tests.
option(BUILD_TESTS "Build unit tests. BUILD_TESTS=OFF implies RUN_TESTS=OFF" ON)
option(RUN_TESTS "Run Tests after successful build. RUN_TESTS=ON will NOT run unit tests if BUILD_TESTS=OFF" OFF)

#add_executable(auto_with_brace_initialization auto_with_brace_initialization.cpp source/common/Singleton.hpp test/common/manual_test.cpp)
#target_link_libraries(auto_with_brace_initialization PRIVATE project_options project_warnings)

#add_subdirectory(RValueReferences)
#add_subdirectory(chrono)
#add_subdirectory(sfinae_and_enable_if)
#add_subdirectory(iterators)
#add_subdirectory(hashes_maps_sets)
#add_subdirectory(random)
#add_subdirectory(constexpr)
#add_subdirectory(lambda_bind_and_related)
#add_subdirectory(CPP_17_20)
#add_subdirectory(python_c_api)
#add_subdirectory(thread_mutex_atomic_lock_free)
#add_subdirectory(practice)
#add_subdirectory(helper_classes)
#add_subdirectory(boost)
add_subdirectory(source)

if(BUILD_TESTS)
    message(NOTICE "building unit tests is enabled")

    # Google test
    find_package(GTest REQUIRED COMPONENTS GTest::gtest_main GTest::gmock_main GTest::gmock GTest::gtest)
    message(STATUS "using GTest ${}, include-path: ${GTest_INCLUDE_DIRS},"
            " libs - ${GTest_LIBS}")

    set(ENABLE_TESTING ON)
    include(CTest)
    include(GoogleTest)
    add_subdirectory(test)
    if(RUN_TESTS)
        # TODO. Code to call ctest to run all the discovered tests.
        message(NOTICE "running unit tests is enabled")
    else()
        message(NOTICE "running unit tests is disabled")
    endif()
else()
    if(RUN_TESTS)
        message(FATAL_ERROR "RUN_TESTS=ON, but unit tests are not built. enable unit tests builds with -DBUILD_TESTS=ON")
    endif()
    message(NOTICE "building unit tests is disabled")
endif()

