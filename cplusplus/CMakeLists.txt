cmake_minimum_required(VERSION 3.27)

set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_SOURCE_DIR}/cmake/flags_override.cmake")
project(cplusplus VERSION 1.0.0 DESCRIPTION "cplusplus" LANGUAGES C CXX)

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

# turn on the dynamic depends for ninja
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
# turn on the experimental API
#set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API  "2182bf5c-ef0d-489a-91da-49dbc3090d2a") # for cmake 3.26
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API  "aa1f7df0-828a-4fcd-9afc-2dc80491aca7") # for cmake 3.27
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    include(cmake/gcc_modules.cmake)
endif()

# Python3
#find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
message(STATUS "using ${Python3_INTERPRETER_ID}, ${Python3_VERSION} executable: ${Python3_EXECUTABLE},"
        " include-path: ${Python3_INCLUDE_DIRS},"
        " libs: ${Python3_LIBRARIES}")

# Boost
#find_package(Boost REQUIRED QUIET COMPONENTS system date_time)
find_package(Boost REQUIRED)
message(STATUS "using Boost ${Boost_VERSION_STRING}, include-path: ${Boost_INCLUDE_DIRS},"
        " libs - ${Boost_LIBRARIES}")

find_package(gRPC REQUIRED)
message(STATUS "using grpc ${gRPC_VERSION_STRING}, include-path: ${gRPC_INCLUDE_DIRS},"
        " libs - ${gRPC_LIBRARIES}")

add_executable(main main.cpp)

add_subdirectory(src)
