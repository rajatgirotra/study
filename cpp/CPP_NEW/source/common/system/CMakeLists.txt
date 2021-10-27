add_library(cscommon STATIC Spinlock.cpp)
target_link_libraries(cscommon PRIVATE project_options project_warnings)


add_executable(csoptions Option.cpp)
target_link_libraries(csoptions PRIVATE project_options project_warnings)
