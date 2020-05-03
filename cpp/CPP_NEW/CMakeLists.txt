cmake_minimum_required(VERSION 3.16)

project(cpp_study DESCRIPTION "cpp starter project makefile" LANGUAGES C CXX)

set(DEVTOOLS_DIR /app/devtools/thirdparty CACHE STRING "location of installed thirdparty libraries" FORCE)

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

# Find Python3
set(ENV{Python3_ROOT_DIR} ${DEVTOOLS_DIR})
set(ENV{LD_LIBRARY_PATH} "$ENV{LD_LIBRARY_PATH}:${DEVTOOLS_DIR}/lib")
message(STATUS "LD_LIBRARY_PATH = $ENV{LD_LIBRARY_PATH}")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
message(STATUS "using ${Python3_INTERPRETER_ID}, ${Python3_VERSION} executable: ${Python3_EXECUTABLE},"
        " include-path: ${Python3_INCLUDE_DIRS},"
        " libs: ${Python3_LIBRARIES}")

# Find Boost
set(ENV{BOOST_ROOT} ${DEVTOOLS_DIR})
find_package(Boost REQUIRED QUIET COMPONENTS system date_time python)
message(STATUS "using Boost ${Boost_VERSION_STRING}, include-path: ${Boost_INCLUDE_DIRS},"
        " libs - ${Boost_LIBRARIES}")

# Find Google-protobuf
set(ENV{Protobuf_SRC_ROOT_FOLDER} ${DEVTOOLS_DIR})
find_package(Protobuf REQUIRED QUIET)
message(STATUS "using google-protobuf ${Protobuf_VERSION}, include-path: ${Protobuf_INCLUDE_DIRS},"
        " libs - ${Protobuf_LIBRARIES}, protoc: ${Protobuf_PROTOC_EXECUTABLE}")

# Find SQLite3
#find_package(SQLite3 REQUIRED QUIET)
#message(STATUS "using sqlite3 ${SQLite3_VERSION}, include-path: ${SQLite3_INCLUDE_DIRS},"
#        " libs - ${SQLite3_LIBRARIES}")

# enable/disable test builds.
option(ENABLE_TESTING "Enable Test Builds" ON)

add_executable(auto_with_brace_initialization auto_with_brace_initialization.cpp)
target_link_libraries(auto_with_brace_initialization PRIVATE project_options project_warnings)

add_subdirectory(RValueReferences)
add_subdirectory(chrono)
add_subdirectory(sfinae_and_enable_if)
add_subdirectory(iterators)
add_subdirectory(hashes_maps_sets)
add_subdirectory(random)
add_subdirectory(constexpr)
add_subdirectory(lambda_bind_and_related)