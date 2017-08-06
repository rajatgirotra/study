cmake_minimum_required (VERSION 2.6)

project(roof CXX)

include_directories(include lib)
## include_directories([AFTER|BEFORE] [SYSTEM] dir1 dir2...)
## Add the given directories to those the compiler uses to search 
## for include files.

add_compile_options(-g -O2 -Wall)

#add_subdirectory(lib obj/lib)
#add_subdirectory(client obj/client)
add_subdirectory(lib)
add_subdirectory(client)
## add_subdirectory(source_dir [binary_dir])
## add a subdirectory to the build. the subdirectory will be
## processed immediately before any command in the current
## CMakeLists.txt is evaluated.

