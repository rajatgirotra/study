add_library(utils SHARED utils.cpp)
#target_link_libraries(utils INTERFACE boost_regex)
target_link_libraries(utils INTERFACE boost_regex)
target_link_libraries(utils INTERFACE "-Wl,-rpath,${Boost_LIBRARY_DIRS}")
