add_executable(sfinae_1 sfinae_1.cpp)
target_link_libraries(sfinae_1 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(sfinae_2 sfinae_2.cpp)
target_link_libraries(sfinae_2 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(enable_if_3 enable_if_3.cpp)
target_link_libraries(enable_if_3 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(enable_if_4 enable_if_4.cpp)
target_link_libraries(enable_if_4 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(enable_if_5 enable_if_5.cpp)
target_link_libraries(enable_if_5 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(sfinae_6 sfinae_6.cpp)
target_link_libraries(sfinae_6 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(sfinae_main_10_1 sfinae_main_10.cpp)
target_compile_definitions(sfinae_main_10_1 PUBLIC VERSION=1)
target_link_libraries(sfinae_main_10_1 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(sfinae_main_10_2 sfinae_main_10.cpp)
target_compile_definitions(sfinae_main_10_2 PUBLIC VERSION=2)
target_link_libraries(sfinae_main_10_2 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(sfinae_main_10_3 sfinae_main_10.cpp)
target_compile_definitions(sfinae_main_10_3 PUBLIC VERSION=3)
target_link_libraries(sfinae_main_10_3 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)