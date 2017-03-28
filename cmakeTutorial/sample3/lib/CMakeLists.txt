set (roof_lib_src roof.cpp)
## We use the set command to create a variable
## roof_lib_src which has the value roof.cpp

add_library(roof SHARED ${roof_lib_src})
## Create a shared library with the name libroof.so, should
## be shared one and containing source files in the 
## roof_lib_src variable.


