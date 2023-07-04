add_executable(range_iterator range_iterator_2.cpp)
target_link_libraries(range_iterator PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(tag_dispatch tag_dispatch_4.cpp)
target_link_libraries(tag_dispatch PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(iterator_adaptor iterator_adaptors_5.cpp)
target_link_libraries(iterator_adaptor PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(reverse_iterator reverse_iterator_6.cpp)
target_link_libraries(reverse_iterator PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_next_prev std_next_prev_7.cpp)
target_link_libraries(std_next_prev PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)