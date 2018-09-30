add_executable(p1 p1.cpp)
target_include_directories(p1 PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(p1 pthread rt)