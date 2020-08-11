add_library(csutil SHARED CStrLen.cpp CSVar.cpp)
target_link_libraries(csutil PRIVATE project_options project_warnings)

add_executable(test_util test_util.cpp)
target_link_libraries(test_util PRIVATE csutil project_options project_warnings)