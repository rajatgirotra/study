#add_library(hello hello.cpp)
# By default add_library will create a static library. So lets create a SHARED library instead

add_library(hello SHARED hello.cpp)
# set_target_properties(hello PROPERTIES NO_SONAME true)
