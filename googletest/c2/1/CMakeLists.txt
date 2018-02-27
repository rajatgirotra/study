add_executable(googletest main.cpp SoundexTest.cpp)
target_link_libraries(googletest PUBLIC GTest::GTest ${GMOCK_LIBRARIES})