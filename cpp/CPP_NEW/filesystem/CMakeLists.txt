add_executable(filesystem_1 filesystem_1.cpp)
target_link_libraries(filesystem_1 PRIVATE pthread project_options project_warnings)

add_executable(filesystem_3 filesystem_3.cpp)
target_link_libraries(filesystem_3 PRIVATE pthread project_options project_warnings)

add_executable(filesystem_5 filesystem_5.cpp)
target_link_libraries(filesystem_5 PRIVATE pthread project_options project_warnings)


