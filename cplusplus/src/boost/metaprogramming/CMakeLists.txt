add_executable(mp_try try.cpp)
target_link_libraries(mp_try PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings Boost::headers)

add_executable(mp_1 mp_1.cpp)
target_link_libraries(mp_1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings Boost::headers)
