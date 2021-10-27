add_library(cscommon STATIC Spinlock.cpp)
target_link_libraries(cscommon PRIVATE project_options project_warnings)


