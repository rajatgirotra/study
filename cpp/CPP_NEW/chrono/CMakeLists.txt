add_executable(chrono_2 2_chrono.cpp)
target_link_libraries(chrono_2 PRIVATE project_options project_warnings)

add_executable(chrono_3 3_chrono.cpp)
target_link_libraries(chrono_3 PRIVATE project_options project_warnings)

add_executable(chrono_4 4_chrono.cpp)
target_link_libraries(chrono_4 PRIVATE project_options project_warnings)

add_executable(chrono_5 5_chrono.cpp)
target_link_libraries(chrono_5 PRIVATE project_options project_warnings)