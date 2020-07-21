cmake_minimum_required(VERSION 3.16)

project(py_c_api DESCRIPTION "py_c_api practice" LANGUAGES C CXX)

#set(ENV{PATH} /home/rajatgirotra/tools:/opt/rh/llvm-toolset-7.0/root/usr/bin:/opt/rh/llvm-toolset-7.0/root/usr/sbin:/opt/rh/devtoolset-9/root/usr/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/rajatgirotra/.local/bin:/home/rajatgirotra/bin)

#set(DEVTOOLS_DIR /app/devtools/thirdparty CACHE STRING "location of installed thirdparty libraries" FORCE)
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
#set(ENV{Python3_ROOT_DIR} ${DEVTOOLS_DIR})



#set(ENV{LD_LIBRARY_PATH} "$ENV{LD_LIBRARY_PATH}:${DEVTOOLS_DIR}/lib")
#message(STATUS "LD_LIBRARY_PATH = $ENV{LD_LIBRARY_PATH}")
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
message(STATUS "using ${Python3_INTERPRETER_ID}, ${Python3_VERSION} executable: ${Python3_EXECUTABLE},"
        " include-path: ${Python3_INCLUDE_DIRS},"
        " libs: ${Python3_LIBRARIES}")

# Find Boost
#set(ENV{BOOST_ROOT} ${DEVTOOLS_DIR})
#find_package(Boost REQUIRED QUIET COMPONENTS system date_time python)
#message(STATUS "using Boost ${Boost_VERSION_STRING}, include-path: ${Boost_INCLUDE_DIRS},"
#        " libs - ${Boost_LIBRARIES}")

# Find Google-protobuf
#set(ENV{Protobuf_SRC_ROOT_FOLDER} ${DEVTOOLS_DIR})
#find_package(Protobuf REQUIRED QUIET)
#message(STATUS "using google-protobuf ${Protobuf_VERSION}, include-path: ${Protobuf_INCLUDE_DIRS},"
#        " libs - ${Protobuf_LIBRARIES}, protoc: ${Protobuf_PROTOC_EXECUTABLE}")

# enable/disable test builds.
#option(ENABLE_TESTING "Enable Test Builds" ON)

add_subdirectory(src)
