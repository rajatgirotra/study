add_executable(print_error print_error.cpp)
target_link_libraries(print_error
    PRIVATE
        ${PROJECT_NAME_LOWERCASE}_project_options
        ${PROJECT_NAME_LOWERCASE}_project_warnings
)