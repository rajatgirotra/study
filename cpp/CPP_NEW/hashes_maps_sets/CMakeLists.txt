add_executable(hash_map hash_map.cpp)
target_link_libraries(hash_map PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(hash_map_create hash_map_create.cpp)
target_link_libraries(hash_map_create PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(hash_map_movable_type hash_map_movable_type.cpp)
target_link_libraries(hash_map_movable_type PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(try_emplace try_emplace.cpp)
target_link_libraries(try_emplace PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)