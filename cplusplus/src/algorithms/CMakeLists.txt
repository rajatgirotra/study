add_executable(algos_all_sortings all_sortings.cpp)
target_link_libraries(algos_all_sortings PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(algos_min_order_statistic min_order_statistic.cpp)
target_link_libraries(algos_min_order_statistic PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(algos_iterate_integers_in_file iterate_integers_in_file.cpp)
target_link_libraries(algos_iterate_integers_in_file PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(algos_two_sum_unsorted two_sum_unsorted.cpp)
target_link_libraries(algos_two_sum_unsorted PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)

add_executable(print_error print_error.cpp)
target_link_libraries(print_error
    PRIVATE
        ${PROJECT_NAME_LOWERCASE}_project_options
        ${PROJECT_NAME_LOWERCASE}_project_warnings
)