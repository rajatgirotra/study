add_executable(sync_timer sync_timer.cpp)
target_link_libraries(sync_timer PRIVATE Boost::headers)

add_executable(async_timer async_timer.cpp)
target_link_libraries(async_timer PRIVATE Boost::headers pthread)

add_executable(async_repeat_timer async_repeat_timer.cpp)
target_link_libraries(async_repeat_timer PRIVATE Boost::headers pthread)

add_executable(async_repeat_timer_handler_function_object async_repeat_timer_handler_function_object.cpp)
target_link_libraries(async_repeat_timer_handler_function_object PRIVATE Boost::headers pthread)

add_executable(strand_usage strand_usage.cpp)
target_link_libraries(strand_usage PRIVATE Boost::headers Boost::thread pthread)

add_executable(sync_daytime_client sync_daytime_client.cpp)
target_link_libraries(sync_daytime_client PRIVATE Boost::headers Boost::thread pthread)

add_executable(sync_daytime_server sync_daytime_server.cpp)
target_link_libraries(sync_daytime_server PRIVATE Boost::headers Boost::thread pthread)

add_executable(async_daytime_server async_daytime_server.cpp)
target_link_libraries(async_daytime_server PRIVATE Boost::headers Boost::thread pthread)

add_executable(sync_daytime_udp_client sync_daytime_udp_client.cpp)
target_link_libraries(sync_daytime_udp_client PRIVATE Boost::headers Boost::thread pthread)

add_executable(sync_daytime_udp_server sync_daytime_udp_server.cpp)
target_link_libraries(sync_daytime_udp_server PRIVATE Boost::headers Boost::thread pthread)

add_executable(async_daytime_udp_server async_daytime_udp_server.cpp)
target_link_libraries(async_daytime_udp_server PRIVATE Boost::headers Boost::thread pthread)

add_executable(allocation allocation.cpp)
target_link_libraries(allocation PRIVATE Boost::headers Boost::thread pthread)

add_executable(ref_counted_buffer ref_counted_buffer.cpp)
target_link_libraries(ref_counted_buffer PRIVATE Boost::headers Boost::thread pthread)

add_executable(chat_client chat_client.cpp)
target_link_libraries(chat_client PRIVATE Boost::headers Boost::thread pthread)

add_executable(chat_server chat_server.cpp)
target_link_libraries(chat_server PRIVATE Boost::headers Boost::thread pthread)
