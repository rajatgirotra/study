add_executable(manual_test manual_test.cpp)
target_include_directories(manual_test PUBLIC ${CMAKE_SOURCE_DIR}/source/)
target_link_libraries(manual_test PRIVATE project_options project_warnings)


add_executable(SingletonTest SingletonTest.cpp)
target_include_directories(SingletonTest PUBLIC ${CMAKE_SOURCE_DIR}/source/ ${GTest_INCLUDE_DIRS})
target_link_libraries(SingletonTest PRIVATE project_options project_warnings GTest::gtest)

# GoogleTest.cmake provides two function gtest_add_tests() and gtest_discover_tests(). Both work differently and call
# add_test() under the hood to add test cases to ctest. These test cases can then be run using ctest command line and also
# uploaded to CDash server.

# gtest_discover_tests is preferred as under the hood it runs --gtests_list_tests option to find out all the tests (including
# parameterized tests) and registers them with ctest using add_test() properly. gtest_add_test() on the other hand uses
# some kind of regular expression to find tests in the tests file, and cannot add parameterized tests properly.
# another advantage of gtest_discover_tests() is that you dont need to run cmake again after modifying your tests.
# with gtest_add_tests() you need to run configure cmake everytime you modify your tests.
# the draw back of gtest_discover_tests() is that adding properties to tests is a bit tedious. properties can be added
# using set_test_properties() command. Run "ctest --show-only=[json-v1|human]" to see the tests available and also
# check out ctest other command line options using ctest --help.
# We will not dwelve into CDash as having your own CDash server has many pre-requisites like Apache/Nginx, MySQL/Postgres,
# PHP, Curl etc etc.
gtest_discover_tests(SingletonTest)
