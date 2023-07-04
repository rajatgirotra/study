add_executable(chrono_2 2_chrono.cpp)
target_link_libraries(chrono_2 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(chrono_3 3_chrono.cpp)
target_link_libraries(chrono_3 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(chrono_4 4_chrono.cpp)
target_link_libraries(chrono_4 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(chrono_5 5_chrono.cpp)
target_link_libraries(chrono_5 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)