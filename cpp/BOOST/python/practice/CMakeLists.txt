add_compile_options("-Wno-deprecated-declarations")

add_library(practice_1_ext SHARED 1.cpp)
set_target_properties(practice_1_ext PROPERTIES PREFIX "")
target_include_directories(practice_1_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(practice_1_ext PUBLIC ${Boost_PYTHON37_LIBRARY})

add_library(practice_2_ext SHARED 2.cpp)
set_target_properties(practice_2_ext PROPERTIES PREFIX "")
target_include_directories(practice_2_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(practice_2_ext PUBLIC ${Boost_PYTHON37_LIBRARY})

add_library(practice_3_ext SHARED 3.cpp)
set_target_properties(practice_3_ext PROPERTIES PREFIX "")
target_include_directories(practice_3_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(practice_3_ext PUBLIC ${Boost_PYTHON37_LIBRARY})

add_library(practice_4_ext SHARED 4.cpp)
set_target_properties(practice_4_ext PROPERTIES PREFIX "")
target_include_directories(practice_4_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(practice_4_ext PUBLIC ${Boost_PYTHON37_LIBRARY})

