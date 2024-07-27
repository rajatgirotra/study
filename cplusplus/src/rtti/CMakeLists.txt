add_executable(rtti_1 1.cpp)
target_link_libraries(rtti_1 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)
