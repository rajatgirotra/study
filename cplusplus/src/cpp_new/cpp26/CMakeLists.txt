add_executable(cpp26_placeholder_name placeholder_name.cpp)
target_link_libraries(cpp26_placeholder_name PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(cpp26_placeholder_name PRIVATE -std=c++2c) # to enable cpp26

add_executable(cpp26_parameter_pack_indexing parameter_pack_indexing.cpp)
target_link_libraries(cpp26_parameter_pack_indexing PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(cpp26_parameter_pack_indexing PRIVATE -std=c++2c) # to enable cpp26

add_executable(cpp26_saturating_math saturating_math.cpp)
target_link_libraries(cpp26_saturating_math PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(cpp26_saturating_math PRIVATE -std=c++2c) # to enable cpp26

add_executable(cpp26_views_concat views_concat.cpp)
target_link_libraries(cpp26_views_concat PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(cpp26_views_concat PRIVATE -std=c++2c) # to enable cpp26

add_executable(cpp26_span_initiailizer_list span_initializer_list.cpp)
target_link_libraries(cpp26_span_initiailizer_list PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_compile_options(cpp26_span_initiailizer_list PRIVATE -std=c++2c) # to enable cpp26

#add_executable(cpp26_signed_unsigned_size_t signed_unsigned_size_t.cpp)
#target_link_libraries(cpp26_signed_unsigned_size_t PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
#target_compile_options(cpp26_signed_unsigned_size_t PRIVATE -std=c++2c)
