add_library(cscommon STATIC Spinlock.cpp Spinlock2.cpp Spinlock3.cpp TicketMutex.cpp)
target_link_libraries(cscommon PRIVATE project_options project_warnings)

