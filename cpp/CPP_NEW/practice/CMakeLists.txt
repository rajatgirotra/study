add_executable(practice_cpp_17 practice.cpp)
target_link_libraries(practice_cpp_17 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(practice_cpp_14 practice.cpp)
target_link_libraries(practice_cpp_14 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_warnings)
target_compile_features(practice_cpp_14 PRIVATE cxx_std_14)

add_executable(practice_jul2021 practice_jul2021.cpp)
target_link_libraries(practice_jul2021 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
#target_compile_features(practice_jul2021 PRIVATE cxx_std_14)

add_executable(lock_free_array lock_free_array.cpp)
target_link_libraries(lock_free_array PRIVATE pthread ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(practice_oct2022 practice_oct2022.cpp)
target_link_libraries(practice_oct2022 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_warnings ${PROJECT_NAME_LOWERCASE}_project_options)
target_compile_features(practice_oct2022 PRIVATE cxx_std_20)