add_executable(tmalf_async_behavior async_behavior_1.cpp)
target_link_libraries(tmalf_async_behavior PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(tmalf_lock_guard lock_guard_4.cpp)
target_link_libraries(tmalf_lock_guard PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(tmalf_threads_in_containers_10 threads_in_containers_10.cpp)
target_link_libraries(tmalf_threads_in_containers_10 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(tmalf_std_call_once_11 std_call_once_11.cpp)
target_link_libraries(tmalf_std_call_once_11 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(tmalf_thread_native_handle_12 thread_native_handle_12.cpp)
target_link_libraries(tmalf_thread_native_handle_12 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(tmalf_thread_hw_concurrency_13 thread_hw_concurrency_13.cpp)
target_link_libraries(tmalf_thread_hw_concurrency_13 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(tmalf_future_16 future_16.cpp)
target_link_libraries(tmalf_future_16 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(tmalf_promise_17 promise_17.cpp)
target_compile_options(tmalf_promise_17 PRIVATE -pthread)
target_link_libraries(tmalf_promise_17 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)

add_executable(packaged_task_18 packaged_task_18.cpp)
target_link_libraries(packaged_task_18 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)

add_executable(reordering_22 reordering_22.cpp)
target_link_libraries(reordering_22 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)
#target_compile_definitions(reordering_22 PRIVATE USE_CPU_FENCE)
#target_compile_definitions(reordering_22 PRIVATE USE_SINGLE_HW_THREAD)

add_executable(lock_free_25 lock_free_25.cpp)
target_link_libraries(lock_free_25 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
target_compile_options(lock_free_25 PRIVATE -masm=intel)
# Figure out how to best generate assembly output.

add_executable(lock_free_28 lock_free_28.cpp)
target_link_libraries(lock_free_28 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
target_compile_options(lock_free_28 PRIVATE -masm=intel)

add_executable(lock_free_29 lock_free_29.cpp)
target_link_libraries(lock_free_29 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
target_compile_options(lock_free_29 PRIVATE -masm=intel)

add_executable(lock_free_30 lock_free_30.cpp)
target_link_libraries(lock_free_30 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings)
target_compile_options(lock_free_30 PRIVATE -masm=intel)

add_executable(lock_free_31 lock_free_31.cpp)
target_link_libraries(lock_free_31 PRIVATE ${PROJECT_NAME_LOWERCASE}::project_options ${PROJECT_NAME_LOWERCASE}::project_warnings pthread)
