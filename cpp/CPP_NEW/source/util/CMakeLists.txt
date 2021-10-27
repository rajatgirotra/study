add_executable(csoptions Switch.cpp OptionProcessor.cpp option_test.cpp )
target_link_libraries(csoptions PRIVATE project_options project_warnings)
