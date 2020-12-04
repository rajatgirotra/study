add_executable(interprocess_1 1_managed_shared_memory.cpp)
target_include_directories(interprocess_1 SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(interprocess_1 ${Boost_DATE_TIME_Library} pthread dl rt)

add_executable(interprocess_2 2_managed_shared_memory.cpp)
target_include_directories(interprocess_2 SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(interprocess_2 ${Boost_DATE_TIME_Library} pthread dl rt)

add_executable(interprocess_3 3_offset_ptr.cpp)
target_include_directories(interprocess_3 SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(interprocess_3 ${Boost_DATE_TIME_Library} pthread dl rt)

add_executable(interprocess_4 4_vector_in_shared_memory.cpp)
target_include_directories(interprocess_4 SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(interprocess_4 ${Boost_DATE_TIME_Library} pthread dl rt)

add_executable(interprocess_5 5_maps_in_shared_memory.cpp)
target_include_directories(interprocess_5 SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(interprocess_5 ${Boost_DATE_TIME_Library} pthread dl rt)
