add_executable(format_1 format_1.cpp)
target_link_libraries(format_1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(format_2 format_2.cpp)
target_link_libraries(format_2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(format_3 format_3.cpp)
target_link_libraries(format_3 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(format_4 format_4.cpp)
target_link_libraries(format_4 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)