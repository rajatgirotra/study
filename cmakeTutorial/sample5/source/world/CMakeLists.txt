#add_library(world world.cpp)
add_library(world SHARED world.cpp)
target_link_libraries(world INTERFACE hello)
# set_target_properties(world PROPERTIES NO_SONAME true)

# Findings, When library hello.so was linked to world.so, -Wl,-rpath was also used. We disabled this by setting CMAKE_SKIP_RPATH in top level CMakeLists.txt

# Next by default, the linker flag -Wl,-soname is enabled, this means the libhello.so has an SONAME. We also confirmed it by using "objdump -p libhello.so | grep SONAME". Due to this we saw that cmake put the path to libhello.so instead of using -lhello as expected and explained in sample2/CMakeLists.txt

# Let see how to disable SO_NAME - Set the NO_SONAME property on the shared library. Let set it now on hello.so

# Also the target_link_libraries() takes a keyword PUBLIC|PRIVATE|INTERFACE
# if we say target_link_libraries(world PUBLIC hello) - it means hello will be linked to world and also be put in the link interface property (so if world is linked to some other library, hello will also be linked to it)
# PRIVATE means - that world will link to hello, but if world is linked to some other library, hello will NOT  be linked to it)
# INTERFACE means - that world will not link to hello, but when world will link to some executable, then hello will link to the executable.

# Lets try all this now
