#add_library(spam SHARED 2_spammify.cpp)
#add_library(spam SHARED 3_spammify.cpp)

#set_target_properties(spam PROPERTIES PREFIX "")
# disable -Wregiser warnings from including Python.h
#target_compile_options(spam PUBLIC -Wno-register)
#target_include_directories(spam SYSTEM PUBLIC ${Python3_INCLUDE_DIRS})
#target_link_libraries(spam PUBLIC debug "" optimized "" general ${Python3_LIBRARIES})

add_executable(embed_python_1 embed_python_1.cpp)
target_include_directories(embed_python_1 SYSTEM PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(embed_python_1 PUBLIC ${Python3_LIBRARIES})

add_executable(embed_python_2 embed_python_2.cpp)
target_include_directories(embed_python_2 SYSTEM PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(embed_python_2 PUBLIC ${Python3_LIBRARIES})

add_executable(embed_python_3 embed_python_3.cpp)
target_include_directories(embed_python_3 SYSTEM PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(embed_python_3 PUBLIC ${Python3_LIBRARIES})

add_executable(embed_python_4 embed_python_4.cpp)
target_include_directories(embed_python_4 SYSTEM PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(embed_python_4 PUBLIC ${Python3_LIBRARIES})

add_executable(embed_python_5 embed_python_5.cpp)
target_include_directories(embed_python_5 SYSTEM PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(embed_python_5 PUBLIC ${Python3_LIBRARIES})

add_executable(embed_python_7 embed_python_7.cpp)
target_include_directories(embed_python_7 SYSTEM PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(embed_python_7 PUBLIC ${Python3_LIBRARIES})

add_library(spam SHARED spammify_8.cpp)
set_target_properties(spam PROPERTIES PREFIX "")
target_include_directories(spam SYSTEM PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(spam PUBLIC ${Python3_LIBRARIES})

#set_target_properties(spam PROPERTIES PREFIX "")
# disable -Wregiser warnings from including Python.h
#target_compile_options(spam PUBLIC -Wno-register)
#target_include_directories(spam SYSTEM PUBLIC ${Python3_INCLUDE_DIRS})
#target_link_libraries(spam PUBLIC debug "" optimized "" general ${Python3_LIBRARIES})
