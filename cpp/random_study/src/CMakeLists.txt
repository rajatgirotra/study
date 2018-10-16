add_executable(shm_hash_map shm_hash_map.cpp)
target_include_directories(shm_hash_map PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(shm_hash_map PUBLIC rt)
target_link_libraries(shm_hash_map PUBLIC -pthread)
target_compile_options(shm_hash_map PUBLIC -pthread)

add_executable(condition_variable condition_variable.cpp)
target_link_libraries(condition_variable PUBLIC -pthread)
target_compile_options(condition_variable PUBLIC -pthread)

add_executable(dbl dbl.cpp)
target_link_libraries(dbl PUBLIC -pthread)
target_compile_options(dbl PUBLIC -pthread)

add_executable(function function.cpp)
target_link_libraries(function PUBLIC -pthread)
target_compile_options(function PUBLIC -pthread)
