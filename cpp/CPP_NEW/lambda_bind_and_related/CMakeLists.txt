add_executable(lambda_1 lambda_1.cpp)
target_link_libraries(lambda_1 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lambda_2 lambda_2.cpp)
target_link_libraries(lambda_2 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lambda_3 lambda_3.cpp)
target_link_libraries(lambda_3 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(bind_1 bind_1.cpp)
target_link_libraries(bind_1 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ref_cref_ref_wrapper ref_cref_ref_wrapper.cpp)
target_link_libraries(ref_cref_ref_wrapper PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(ref_cref_ref_wrapper_2 ref_cref_ref_wrapper_2.cpp)
target_link_libraries(ref_cref_ref_wrapper_2 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lamda_vs_bind lamda_vs_bind.cpp)
target_link_libraries(lamda_vs_bind PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lambda_to_implement lambda_to_implement.cpp)
target_link_libraries(lambda_to_implement PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(async async.cpp)
target_link_libraries(async PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(lambda_4_hello_world lambda_4_hello_world.cpp)
target_link_libraries(lambda_4_hello_world PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lambda_5_fibonacci lambda_5_fibonacci.cpp)
target_link_libraries(lambda_5_fibonacci PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lambda_6_inherit lambda_6_inherit.cpp)
target_link_libraries(lambda_6_inherit PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lambda_sorcery_7 lambda_sorcery_7.cpp)
target_link_libraries(lambda_sorcery_7 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(lambda_this_8 lambda_this_8.cpp)
target_link_libraries(lambda_this_8 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
