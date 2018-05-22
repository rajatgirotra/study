add_compile_options("-Wno-deprecated-declarations")

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


add_library(base_derived_ext SHARED base_derived.cpp)
set_target_properties(base_derived_ext PROPERTIES PREFIX "")
target_include_directories(base_derived_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(base_derived_ext PUBLIC ${Boost_PYTHON27_LIBRARY})


add_library(abstract_ext SHARED abstract.cpp)
set_target_properties(abstract_ext PROPERTIES PREFIX "")
target_include_directories(abstract_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(abstract_ext PUBLIC ${Boost_PYTHON27_LIBRARY})

add_library(virtual_ext SHARED virtual.cpp)
set_target_properties(virtual_ext PROPERTIES PREFIX "")
target_include_directories(virtual_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(virtual_ext PUBLIC ${Boost_PYTHON27_LIBRARY})

add_library(override_ext SHARED override.cpp)
set_target_properties(override_ext PROPERTIES PREFIX "")
target_include_directories(override_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(override_ext PUBLIC ${Boost_PYTHON27_LIBRARY})

add_library(call_policy_ext SHARED call_policy.cpp)
set_target_properties(call_policy_ext PROPERTIES PREFIX "")
target_include_directories(call_policy_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(call_policy_ext PUBLIC ${Boost_PYTHON27_LIBRARY})

add_library(my_list_ext SHARED list.cpp)
set_target_properties(my_list_ext PROPERTIES PREFIX "")
target_include_directories(my_list_ext PUBLIC ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(my_list_ext PUBLIC ${Boost_PYTHON27_LIBRARY})