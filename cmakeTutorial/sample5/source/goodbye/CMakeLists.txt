add_library(goodbye SHARED goodbye.cpp)
target_link_libraries(goodbye INTERFACE world)
