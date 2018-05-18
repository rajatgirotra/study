#add_library(spam SHARED 2_spammify.cpp)
add_library(spam SHARED 3_spammify.cpp)

set_target_properties(spam PROPERTIES PREFIX "")
# disable -Wregiser warnings from including Python.h
target_compile_options(spam PUBLIC -Wno-register)
target_include_directories(spam PUBLIC ${PYTHON_INCLUDE_DIRS})
target_link_libraries(spam PUBLIC debug "" optimized "" general ${PYTHON_LIBRARIES})