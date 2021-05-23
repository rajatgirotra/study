add_executable(manual_test manual_test.cpp)
target_include_directories(manual_test PUBLIC ${CMAKE_SOURCE_DIR}/source/)
target_link_libraries(manual_test PRIVATE project_options project_warnings)


add_executable(SingletonTest SingletonTest.cpp)
target_include_directories(SingletonTest PUBLIC ${CMAKE_SOURCE_DIR}/source/ ${GTest_INCLUDE_DIRS})
target_link_libraries(SingletonTest PRIVATE project_options project_warnings GTest::gtest)

#gtest_discover_tests
