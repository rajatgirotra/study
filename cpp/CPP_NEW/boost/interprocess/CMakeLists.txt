add_executable(interprocess_1 1_managed_shared_memory.cpp)
target_link_libraries(interprocess_1 PRIVATE Boost::date_time)

add_executable(interprocess_2 2_managed_shared_memory.cpp)
target_link_libraries(interprocess_2 PRIVATE Boost::date_time)

add_executable(interprocess_3 3_offset_ptr.cpp)
target_link_libraries(interprocess_3 PRIVATE Boost::date_time)

add_executable(interprocess_4 4_vector_in_shared_memory.cpp)
target_link_libraries(interprocess_4 PRIVATE Boost::date_time)

add_executable(interprocess_5 5_maps_in_shared_memory.cpp)
target_link_libraries(interprocess_5 PRIVATE Boost::date_time)
