add_library(modules_square)
target_link_libraries(modules_square PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_sources(modules_square PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES mod0_pmiu.cppm)

add_executable(modules_mod0main mod0main.cpp)
target_link_libraries(modules_mod0main PRIVATE modules_square ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
#set_property(TARGET modules_mod0main PROPERTY CXX_SCAN_FOR_MODULES 1) # this also works.
set_property(SOURCE mod0main.cpp PROPERTY CXX_SCAN_FOR_MODULES 1) # and this also works.

add_library(modules_mymodule)
target_link_libraries(modules_mymodule PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_sources(modules_mymodule PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES mod1_pmiu.cppm mod1_internal_partition.cppp mod1_interface_partition.cppm)
# mod1_implementation_unit.cpp is not an interface partition or a primary interface unit. So it should not be present
# in the CXX_MODULES file set.
set_source_files_properties(mod1_internal_partition.cppp PROPERTIES LANGUAGE CXX) # to register .cppp as a C++ file extension

add_executable(modules_mod1main mod1main.cpp mod1_implementation_unit.cpp)
target_link_libraries(modules_mod1main PRIVATE modules_mymodule ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
set_property(TARGET modules_mod1main PROPERTY CXX_SCAN_FOR_MODULES 1) # this also works.
# set_property(SOURCE mod1main.cpp PROPERTY CXX_SCAN_FOR_MODULES 1) # and this also works.
