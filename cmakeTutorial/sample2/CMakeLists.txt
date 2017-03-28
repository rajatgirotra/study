cmake_minimum_required (VERSION 3.5.1)

project(project2 VERSION 1.0.0 LANGUAGES C CXX)

add_compile_options(-g -Wall)

add_executable(crypto main.c)

target_link_libraries(crypto crypt)
## Link a target to given libraries
## target_link_libraries(<target> [item1 [item2 [...]]]
##	[[debug|optimized|general] <item>] ...)
## Specify libraries or flags to use when linking a given target. The target must have been created in the current
## directory by a command such as add_executable or add_library.
## lets spend some more time on this one.
## the <item> argument to this command can be:
## 1. A library target name - Let say in some other part of the code base, you have created a library "foo" (libfoo.so) using add_library(foo, args) function. Then the item argument here can be "foo". Cmake will automatically generate correct dependeny rules to make sure libfoo.so is built first.

##. 2 - item can be an imported target. Imported targets are executables/libraries which are 3rd party and not part of your buildsystem. You can add them using add_library() with the IMPORTED parameter set. We'll see this in a bit. If cmake finds that a library has no embedded SO_NAME, it will ask the linker to search for library foo by saying "-lfoo" on the command line. Otherwise if a library has SO_NAME, cmake will put the complete path to the library when giving to linker.

## 3 - A plain library name - like above (crypt). cmake just tell the linker to find libcrypt.so using -lcrypt

## A 'debug'. 'optimized', 'general' keyword followed by item means to link only for that Configuration.
## study how to set different configurations in cmake

## A linker flag - Item starting with dash "-" but not -l or -framework are treated as linker flags but these should be created as PRIVATE_LINKS otherwise the flag applies to all children also.

## By default, library dependencies are transitive. This means that if target A depends on target B, then when target C depends on target A, target B will also be linked as it required by target A. We can control this by specifying PRIVATE/PUBLIC/INTERFACE keywords.
# target_link_libraries(MYTARGET, MYLIBRARY)
# PRIVATE - means that MYTARGET will link to MYLIBRARY but will not be part of the link interface.
# PUBLIC - means that MYTARGET will link to MYLIBRARY AND will ALSO be part of the link interface.
# INTERFACE - means that MYTARGET WILL NOT link to MYLIBRARY BUT WILL BE part of the link interface.
# We can check several properties to see what is part of link interface and what is not.

# Lets test all these in new sample5
