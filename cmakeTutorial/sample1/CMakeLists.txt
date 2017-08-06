## in CMake you have the notion of separate build and source directory tree.
## So your source tree is never made dirty, and you can have multiple
## build trees to support different compilers.
## Always separate your build tree from source tree. Do
## mkdir build
## cd build
## cmake <project_root>
## make

cmake_minimum_required (VERSION 3.5.1)
## The minimum version of cmake required to build a project. if the version
## detected is lower than this, a fatal error will be reported.

project(project1 VERSION 1.1.0 LANGUAGES C CXX)
## some name to give to your project. Must be specified directly in the top level CMakeLists.txt and not via the include() command. Can be any arbitrary name, optionally
## followed by a VERSION number followed by list of languages supported by your project.
## Syntax: project(<projectName> VERSION version LANGUAGES [language1 languag2...])
## CXX for c++, C for c, Fortran etc.
## It sets the following variables too
message(${PROJECT_SOURCE_DIR})
message(${PROJECT_BINARY_DIR})
message(${project1_SOURCE_DIR})
message(${project1_BINARY_DIR})
message(${CMAKE_SOURCE_DIR})
message(${CMAKE_BINARY_DIR})
message(${PROJECT_VERSION})
message(${project1_VERSION})
message(${PROJECT_VERSION_MAJOR})
message(${PROJECT_VERSION_MINOR})
message(${PROJECT_VERSION_PATCH})
# message(${PROJECT_VERSION_PATCH_TWEAK}) ## no tweal no is set, so this will error.
## Actually cmake set's both PROJECT_VERSION and project1_VERSION and other also like that.

## the message command itself it pretty simple. It can also take an optional first argument which is the mode (level) of information, like STATUS, WARNING, FATAL_ERROR, SEND_ERROR etc. See the help for more
message("NO_MODE")
message(STATUS "STATUS MODE")
message(WARNING "WARNING MODE")
message(AUTHOR_WARNING "AUTHOR_WARNING MODE")
#message(SEND_ERROR "SEND_ERROR MODE")
message(DEPRECATION "DEPRECATION MODE")
# message(FATAL_ERROR "FATAL_ERROR MODE") # Will cause cmake to stop

add_definitions(-DABC -DFOO=10)
## Used to pass -D flags & other flags to the compiler for targets in the current directory and below.
## really dont abuse this and use add_compile_options() for adding compiler options like -g -Wall etc.
## this command also sets the COMPILE_DEFINITIONS property for the current directory.
## Each directory with source files inherits the value of this property from its parent. COMPILE_DEFINITIONS
## is a list of semicolon separated list of compiler definitions to be passed to compiler. Also we have
## COMPILE_DEFINITIONS_CONFIG property ( where CONFIG can be DEBUG, RELEASE) etc and you can set the value of these
## properties. For setting properties, we have the set_property() command, we'll explore this later
## Lets try to get the property and display using message() command

get_directory_property(COMPILE_DEFS DIRECTORY . COMPILE_DEFINITIONS)
message("Compile definitions = " ${COMPILE_DEFS})

# ditto like add_definitions. property name is COMPILE_OPTIONS
add_compile_options(-std=c++14 -g -Wall)
get_directory_property(COMPILE_OPTS DIRECTORY . COMPILE_OPTIONS)
message("Compile options = " ${COMPILE_OPTS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}) # sets the RUNTIME_OUTPUT_DIRECTORY on all subsequent targets
add_executable(simple main.cpp)
set_property(TARGET simple PROPERTY OUTPUT_NAME rajat_simple)

get_target_property(VALUE_ROD simple RUNTIME_OUTPUT_DIRECTORY)
message("RUNTIME_OUTPUT_DIRECTORY is ${VALUE_ROD}")
## add_executable(<name> [WIN32] [MACOX_BUNDLE] [EXCLUDE_FROM_ALL]
##		   source1 source2 source3... sourceN)
## Adds an executable target called <name> to be built from the source files
## listed in the command invocation. name is the logical name. Depending on platform cmake will put the suffix like
## .exe or nothing. Also the executable is stored in the build tree at the directory location as the source files.
## You can check target properties like RUNTIME_OUTPUT_DIRECTORY and OUTPUT_NAME and EXCLUDE_FROM_ALL to understand each one.
## RUNTIME_OUTPUT_DIRECTORY is used to change the output directory.
## OUTPUT_NAME is used to change the final output name
## EXCLUDE_FROM_ALL - means do not add targets in this subdirectory to the list of ALL targets to be built. This can be done for directories which are part of your build but do not always need to be built. For example, samples in an example folder.
