add_executable(about_unique_ptrs_1 about_unique_ptrs_1.cpp)
target_link_libraries(about_unique_ptrs_1 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(about_shared_ptrs_2 about_shared_ptrs_2.cpp)
target_link_libraries(about_shared_ptrs_2 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(const_unique_ptr_in_class_3 const_unique_ptr_in_class_3.cpp)
target_link_libraries(const_unique_ptr_in_class_3 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
