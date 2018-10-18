add_executable(RValueReferences_1 1.cpp)
#[[
target_include_directories(main PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(main PUBLIC rt)
target_link_libraries(main PUBLIC -pthread)
target_compile_options(main PUBLIC -pthread)
]]

add_executable(RValueReferences_2 2.cpp)
add_executable(RValueReferences_3 3.cpp)
add_executable(RValueReferences_6 6.cpp)
add_executable(RValueReferences_11 11.cpp)