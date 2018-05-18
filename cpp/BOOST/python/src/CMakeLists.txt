add_library(hello_ext SHARED hello_world.cpp)
set_target_properties(hello_ext PROPERTIES PREFIX "")
target_include_directories(hello_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(hello_ext PUBLIC ${Boost_PYTHON27_LIBRARY})

add_library(world_ext SHARED world.cpp)
set_target_properties(world_ext PROPERTIES PREFIX "")
target_include_directories(world_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(world_ext PUBLIC ${Boost_PYTHON27_LIBRARY})

add_library(cruel_ext SHARED cruel.cpp)
set_target_properties(cruel_ext PROPERTIES PREFIX "")
target_include_directories(cruel_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(cruel_ext PUBLIC ${Boost_PYTHON27_LIBRARY})

add_library(data_member_ext SHARED data_member.cpp)
set_target_properties(data_member_ext PROPERTIES PREFIX "")
target_include_directories(data_member_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(data_member_ext PUBLIC ${Boost_PYTHON27_LIBRARY})