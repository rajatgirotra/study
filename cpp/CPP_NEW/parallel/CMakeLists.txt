add_executable(new_algorithms_3 new_algorithms_3.cpp)
target_link_libraries(new_algorithms_3 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
