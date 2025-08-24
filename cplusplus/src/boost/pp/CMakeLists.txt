add_executable(pp_1 pp_1.cpp)
target_link_libraries(pp_1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings Boost::headers)

add_executable(pp_2 pp_2.cpp)
target_include_directories(pp_2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pp_2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings Boost::headers)
