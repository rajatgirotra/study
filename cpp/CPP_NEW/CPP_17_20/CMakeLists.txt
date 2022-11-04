add_executable(mix_1 mix_1.cpp)
target_link_libraries(mix_1 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(mix_2 mix_2.cpp)
target_link_libraries(mix_2 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(evaluation_order_4 evaluation_order_4.cpp)
target_link_libraries(evaluation_order_4 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(structured_bindings_5 structured_bindings_5.cpp)
target_link_libraries(structured_bindings_5 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(variable_template_6 variable_template_6.cpp)
target_include_directories(variable_template_6 SYSTEM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(variable_template_6 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(variable_template_7 variable_template_7.cpp)
target_link_libraries(variable_template_7 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_optional_8 std_optional_8.cpp)
target_link_libraries(std_optional_8 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_variant_9 std_variant_9.cpp)
target_link_libraries(std_variant_9 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_variant_10 std_variant_10.cpp)
target_link_libraries(std_variant_10 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_variant_11 std_variant_11.cpp)
target_link_libraries(std_variant_11 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_variant_12 std_variant_12.cpp)
target_link_libraries(std_variant_12 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_variant_13 std_variant_13.cpp)
target_link_libraries(std_variant_13 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_14 concepts_14.cpp)
target_link_libraries(concepts_14 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
target_compile_options(concepts_14 PRIVATE -fconcepts)

add_executable(fold_expressions_15 fold_expressions_15.cpp)
target_link_libraries(fold_expressions_15 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(inline_variables_16 inline_variables.cpp inline_variables_16.cpp)
target_link_libraries(inline_variables_16 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(fold_expressions_17 fold_expressions_17.cpp)
target_link_libraries(fold_expressions_17 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(fold_expressions_18 fold_expressions_18.cpp)
target_link_libraries(fold_expressions_18 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(fold_expressions_19 fold_expressions_19.cpp)
target_link_libraries(fold_expressions_19 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(if_constexpr_20 if_constexpr_20.cpp)
target_link_libraries(if_constexpr_20 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(has_include_21 has_include_21.cpp)
target_link_libraries(has_include_21 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(non_type_auto_template_22 non_type_auto_template_22.cpp)
target_link_libraries(non_type_auto_template_22 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(template_paramter_23 template_paramter_23.cpp)
target_link_libraries(template_paramter_23 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_any_24 std_any_24.cpp)
target_link_libraries(std_any_24 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_string_view_25 std_string_view_25.cpp)
target_link_libraries(std_string_view_25 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_string_view_26 std_string_view_26.cpp)
target_link_libraries(std_string_view_26 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(charconv_functions_27 charconv_functions_27.cpp)
target_link_libraries(charconv_functions_27 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(string_search_28 string_search_28.cpp)
target_link_libraries(string_search_28 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(std_byte_29 std_byte_29.cpp)
target_link_libraries(std_byte_29 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(container_extract_method_30 container_extract_method_30.cpp)
target_link_libraries(container_extract_method_30 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(integer_sequence_31 integer_sequence_31.cpp)
target_link_libraries(integer_sequence_31 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(spaceship_operator_32 spaceship_operator_32.cpp)
target_link_libraries(spaceship_operator_32 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(spaceship_operator_33 spaceship_operator_33.cpp)
target_link_libraries(spaceship_operator_33 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(spaceship_operator_34 spaceship_operator_34.cpp)
target_link_libraries(spaceship_operator_34 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(auto_parameters_35 auto_parameters_35.cpp)
target_link_libraries(auto_parameters_35 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_36 concepts_36.cpp)
target_link_libraries(concepts_36 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_37 concepts_37.cpp)
target_link_libraries(concepts_37 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_38 concepts_38.cpp)
target_link_libraries(concepts_38 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_39 concepts_39.cpp)
target_link_libraries(concepts_39 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_40 concepts_40.cpp)
target_link_libraries(concepts_40 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_41 concepts_41.cpp)
target_link_libraries(concepts_41 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_42 concepts_42.cpp)
target_link_libraries(concepts_42 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_43 concepts_43.cpp)
target_link_libraries(concepts_43 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(concepts_44 concepts_44.cpp)
target_link_libraries(concepts_44 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_46 ranges_and_views_46.cpp)
target_link_libraries(ranges_and_views_46 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_47 ranges_and_views_47.cpp)
target_link_libraries(ranges_and_views_47 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_48 ranges_and_views_48.cpp)
target_link_libraries(ranges_and_views_48 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_49 ranges_and_views_49.cpp)
target_link_libraries(ranges_and_views_49 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_50 ranges_and_views_50.cpp)
target_link_libraries(ranges_and_views_50 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_51 ranges_and_views_51.cpp)
target_link_libraries(ranges_and_views_51 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_52 ranges_and_views_52.cpp)
target_link_libraries(ranges_and_views_52 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_53 ranges_and_views_53.cpp)
target_link_libraries(ranges_and_views_53 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_54 ranges_and_views_54.cpp)
target_link_libraries(ranges_and_views_54 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ranges_and_views_55 ranges_and_views_55.cpp)
target_link_libraries(ranges_and_views_55 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(jthread_56 jthread_56.cpp)
target_link_libraries(jthread_56 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(jthread_57 jthread_57.cpp)
target_link_libraries(jthread_57 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(jthread_58 jthread_58.cpp)
target_link_libraries(jthread_58 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(jthread_59 jthread_59.cpp)
target_link_libraries(jthread_59 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(jthread_60 jthread_60.cpp)
target_link_libraries(jthread_60 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(stop_source_stop_token_61 stop_source_stop_token_61.cpp)
target_link_libraries(stop_source_stop_token_61 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(jthread_62 jthread_62.cpp)
target_link_libraries(jthread_62 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(latch_barrier_63 latch_barrier_63.cpp)
target_link_libraries(latch_barrier_63 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(semaphore_64 semaphore_64.cpp)
target_link_libraries(semaphore_64 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(coroutine_66 coroutine_66.cpp)
target_link_libraries(coroutine_66 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(coroutine_67 coroutine_67.cpp)
target_link_libraries(coroutine_67 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(coroutine_69 coroutine_69.cpp)
target_link_libraries(coroutine_69 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(coroutine_70 coroutine_70.cpp)
target_link_libraries(coroutine_70 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(coroutine_71 coroutine_71.cpp)
target_link_libraries(coroutine_71 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(coroutine_73 coroutine_73.cpp)
target_link_libraries(coroutine_73 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(scratch scratch.cpp)
target_link_libraries(scratch PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
