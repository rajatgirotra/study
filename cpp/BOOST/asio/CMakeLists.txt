cmake_minimum_required(VERSION 3.5.0)

project(asio VERSION 1.0.0 LANGUAGES C CXX)

find_package(Boost REQUIRED COMPONENTS thread system chrono date_time)

if (NOT ${Boost_FOUND})
  message(FATAL_ERROR "Could not find Boost to build project")
endif()

add_compile_options(-std=c++11)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

add_executable(sync_timer 9_sync_timer.cpp)
target_include_directories(sync_timer SYSTEM PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(sync_timer ${Boost_DATE_TIME_LIBRARY} ${Boost_SYSTEM_LIBRARY})

# add_executable(sync_timer 9_sync_timer.cpp)
# add_executable(async_timer 10_sync_timer.cpp)
# add_executable(argument_binding 11_argument_binding.cpp)
# add_executable(timer_in_class 12_timer_in_class.cpp)
# add_executable(strand 13_strand.cpp)
