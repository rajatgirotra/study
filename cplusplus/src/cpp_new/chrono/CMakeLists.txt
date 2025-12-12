add_executable(chrono_2 2_chrono.cpp)
target_link_libraries(chrono_2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(chrono_2 PRIVATE -std=c++2c)

add_executable(chrono_3 3_chrono.cpp)
target_link_libraries(chrono_3 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(chrono_3 PRIVATE -std=c++2c)

add_executable(chrono_4 4_chrono.cpp)
target_link_libraries(chrono_4 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(chrono_4 PRIVATE -std=c++2c)

add_executable(chrono_5 5_chrono.cpp)
target_link_libraries(chrono_5 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(chrono_5 PRIVATE -std=c++2c)
