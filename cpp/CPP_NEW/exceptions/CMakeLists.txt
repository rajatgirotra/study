add_executable(exceptions_3 3_exceptions.cpp)
target_link_libraries(exceptions_3 PRIVATE pthread ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(exceptions_4 4_exceptions.cpp)
target_link_libraries(exceptions_4 PRIVATE pthread ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(exceptions_6 6_exceptions.cpp)
target_link_libraries(exceptions_6 PRIVATE pthread ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(exceptions_7 7_exceptions.cpp)
target_link_libraries(exceptions_7 PRIVATE pthread ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
