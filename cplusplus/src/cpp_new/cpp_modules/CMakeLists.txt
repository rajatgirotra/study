add_library(modules_square)

target_link_libraries(modules_square PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_sources(modules_square PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES mod0.cppm)

add_executable(modules_mod0main mod0main.cpp)
target_link_libraries(modules_mod0main PRIVATE modules_square ${PROJECT_NAME_LOWERCASE}_project_options ${PROJECT_NAME_LOWERCASE}_project_warnings)
set_property(TARGET modules_mod0main PROPERTY CXX_SCAN_FOR_MODULES 1)


