cmake_minimum_required(VERSION 3.5.1)

project (sample5 VERSION 1.0.0 LANGUAGES C CXX)

add_compile_options(-g -Wall -std=gnu++1y)

# Lets add an imported library - Google Protobuf
add_library(protobuf SHARED IMPORTED GLOBAL)

set (CMAKE_SKIP_RPATH false)

# Hello subdirectory will have a single function to print Hello
add_subdirectory(hello)
# World subdirectory will have a single function to print World
add_subdirectory(world)
# world actually depends on hello to print hello() first and then world()

# CMake and RPATH - In Cmake you have a build tree and you also have an install tree. Ie where binaries are finally installed for packaging up. From 2.6 CMAKE onwards, CMake uses -Wl,-rpath by default whn doing builds. All binaries in the build tree contain rpaths to libraries in the build tree. When you later run the install command, the rpath by default removed. However there are a number of variables using which we can tailor the use of RPATH. Lets see

# CMAKE_INSTALL_RPATH= A semicolon separated list of rpaths to use during install phase
# CMAKE_SKIP_RPATH=true <Do not add RPATH to targets at all.
# CMAKE_INSTALL_RPATH_USE_LINK_PATH = false --> means if cmake finds some RPATH which refers to location outside the build tree, then dont add these paths to the install rpath (should be false mostly, as cmake will definitely find rpaths to 3rd party  libraries) 
# CMAKE_BUILD_WITH_INSTALL_RPATH = CMAKE builds will use the install rpath, not the build rpath.
# CMAKE_INSTALL_PREFIX=default install location is /usr/local on linux.When u run "make install" this prefix is where installation happens.
# Read the install() command to learn about installing
# just in case you need to have different RPATH settings for different targets, you can set target properties for those targets, using the set_target_properties() command. Properties names are similar but without the CMAKE_ prefix.

add_subdirectory(goodbye)

add_subdirectory(main)
