cmake_minimum_required(VERSION 3.16)

project(cpp_starter_project DESCRIPTION "cpp starter project makefile" LANGUAGES C CXX)
set(CMAKE_PREFIX_PATH /app/devtools/thirdparty)

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

# sanitizer options if supported by the compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# enable/disable test builds.
option(ENABLE_TESTING "Enable Test Builds" ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(auto_with_brace_initialization auto_with_brace_initialization.cpp)
target_link_libraries(auto_with_brace_initialization PRIVATE project_options project_warnings)

add_subdirectory(RValueReferences)
add_subdirectory(chrono)
add_subdirectory(sfinae_and_enable_if)
add_subdirectory(iterators)
add_subdirectory(hashes_maps_sets)
add_subdirectory(random)
add_subdirectory(constexpr)