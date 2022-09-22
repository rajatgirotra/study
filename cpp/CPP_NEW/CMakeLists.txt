cmake_minimum_required(VERSION 3.17)

set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_SOURCE_DIR}/cmake/flags_override.cmake")

project(cpp_study VERSION 1.0.0 DESCRIPTION "cpp starter project makefile" LANGUAGES C CXX)

string(TOLOWER ${CMAKE_PROJECT_NAME} PROJECT_NAME_LOWERCASE)
set(PROJECT_TARGETS ${PROJECT_NAME_LOWERCASE}Targets)

include(cmake/StandardProjectSettings.cmake)

# create an interface target. and attach project wide compiler warnings to it.
add_library(${PROJECT_NAME_LOWERCASE}_project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME_LOWERCASE}_project_warnings)
add_library(${PROJECT_NAME_LOWERCASE}::project_warnings ALIAS ${PROJECT_NAME_LOWERCASE}_project_warnings)
install(TARGETS ${PROJECT_NAME_LOWERCASE}_project_warnings EXPORT ${PROJECT_TARGETS})

# create an interface target. we can attach cmake properties to this library which will apply globally to our build.
add_library(${PROJECT_NAME_LOWERCASE}_project_options INTERFACE)

# cmake now has its own dataset of compilers names, versions and the features that are supported by those compiler versions
# CMAKE_CXX_KNOWN_FEATURES is a list of all c++ features known to cmake. CMAKE_CXX_COMPILE_FEATURES is a subset of CMAKE_CXX_KNOWN_FEATURES
# which can be used to turn off/on certain flags. Here we use one such feature to turn on C++17 flag
# target_compile_features(project_options INTERFACE cxx_std_20) # we control this through the toolchain generator in conan

# set compile/link options
include(cmake/CompilerFlags.cmake)
set_project_flags(${PROJECT_NAME_LOWERCASE}_project_options)

# sanitizer options if supported by the compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(${PROJECT_NAME_LOWERCASE}_project_options)

add_library(${PROJECT_NAME_LOWERCASE}::project_options ALIAS ${PROJECT_NAME_LOWERCASE}_project_options)
install(TARGETS ${PROJECT_NAME_LOWERCASE}_project_options EXPORT ${PROJECT_TARGETS})

# enable doxygen
#include(cmake/Doxygen.cmake)
#enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# Python3
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
message(STATUS "using ${Python3_INTERPRETER_ID}, ${Python3_VERSION} executable: ${Python3_EXECUTABLE},"
        " include-path: ${Python3_INCLUDE_DIRS},"
        " libs: ${Python3_LIBRARIES}")

# Boost
find_package(Boost REQUIRED QUIET COMPONENTS system date_time)
message(STATUS "using Boost ${Boost_VERSION_STRING}, include-path: ${Boost_INCLUDE_DIRS},"
        " libs - ${Boost_LIBRARIES}")

## Google Benchmark
find_package(benchmark 1.5.3 EXACT REQUIRED QUIET COMPONENTS)
message(STATUS "using Google Benchmark ${}, include-path: ${benchmark_INCLUDE_DIRS},"
        " libs - ${benchmark_LIBS}")

# Find SQLite3
find_package(SQLite3 3.38.5 EXACT REQUIRED QUIET)
message(STATUS "using sqlite3 ${SQLite3_VERSION}, include-path: ${SQLite3_INCLUDE_DIRS},"
        " libs - ${SQLite3_LIBRARIES}")

# find valgrind program
find_program(VALGRIND_EXECUTABLE NAMES valgrind REQUIRED)
message(STATUS "using valgrind: ${VALGRIND_EXECUTABLE}")

# Find Google-protobuf
find_package(Protobuf REQUIRED QUIET)
message(STATUS "using google-protobuf ${Protobuf_VERSION}, include-path: ${Protobuf_INCLUDE_DIRS},"
        " libs - ${Protobuf_LIBRARIES}, protoc: ${Protobuf_PROTOC_EXECUTABLE}")

# enable/disable test builds and running tests.
option(BUILD_TESTS "Build unit tests. BUILD_TESTS=OFF implies RUN_TESTS=OFF" OFF)
option(RUN_TESTS "Run Tests after successful build. RUN_TESTS=ON will NOT run unit tests if BUILD_TESTS=OFF" OFF)

#add_executable(auto_with_brace_initialization auto_with_brace_initialization.cpp source/common/Singleton.hpp test/common/manual_test.cpp)
#target_link_libraries(auto_with_brace_initialization PRIVATE project_options project_warnings)

#add_subdirectory(boost)
#add_subdirectory(chrono)
#add_subdirectory(constexpr)
#add_subdirectory(hashes_maps_sets)
#add_subdirectory(sfinae_and_enable_if)
#add_subdirectory(iostreams)
#add_subdirectory(iterators)
#add_subdirectory(RValueReferences)
#add_subdirectory(lambda_bind_and_related)
#add_subdirectory(thread_mutex_atomic_lock_free)
add_subdirectory(CPP_17_20)
#add_subdirectory(exceptions)
#add_subdirectory(python_c_api)
#add_subdirectory(practice)
#add_subdirectory(random)
#add_subdirectory(helper_classes)
#add_subdirectory(source)
#add_subdirectory(filesystem)
#add_subdirectory(parallel)
#add_subdirectory(smart_pointers)
#add_subdirectory(orderbook)

#if(BUILD_TESTS)
#    message(NOTICE "building unit tests is enabled")
#
#    # Google test
#    #    find_package(GTest REQUIRED COMPONENTS GTest::gtest_main GTest::gmock_main GTest::gmock GTest::gtest)
#    include(FetchContent)
#    FetchContent_Declare(
#            googletest
#            GIT_REPOSITORY https://github.com/google/googletest.git
#            GIT_TAG origin/master # master
#         #  GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 # release 1.11.0
#    )
#
#    # For Windows: Prevent overriding the parent project's compiler/linker settings
#    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#    FetchContent_MakeAvailable(googletest)
#
#    message(STATUS "googletest populated: ${googletest_POPULATED}, src dir: ${googletest_SOURCE_DIR}, build dir: ${googletest_BINARY_DIR}")
#    set(ENABLE_TESTING ON)
#    include(CTest)
#    include(GoogleTest)
#    add_subdirectory(test)
#    if(RUN_TESTS)
#        # TODO. Code to call ctest to run all the discovered tests.
#        message(NOTICE "running unit tests is enabled")
#    else()
#        message(NOTICE "running unit tests is disabled")
#    endif()
#else()
#    if(RUN_TESTS)
#        message(FATAL_ERROR "RUN_TESTS=ON, but unit tests are not built. enable unit tests builds with -DBUILD_TESTS=ON")
#    endif()
#    message(NOTICE "building unit tests is disabled")
#endif()
#
