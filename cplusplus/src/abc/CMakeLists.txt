add_executable(abc_1 1.cpp)
target_link_libraries(abc_1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(abc_2 2.cpp)
target_link_libraries(abc_2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(abc_3 3.cpp)
target_link_libraries(abc_3 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(abc_4 4.cpp)
target_link_libraries(abc_4 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(abc_5 5.cpp)
target_link_libraries(abc_5 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(abc_6 6.cpp)
target_link_libraries(abc_6 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(abc_7 7.cpp)
target_link_libraries(abc_7 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)
