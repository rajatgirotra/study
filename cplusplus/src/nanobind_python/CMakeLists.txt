nanobind_add_module(ext_1 NOMINSIZE ext_1.cpp)
target_link_libraries(ext_1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

nanobind_add_module(ext_2 NOMINSIZE ext_2.cpp)
target_link_libraries(ext_2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
