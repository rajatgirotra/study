add_library(utils SHARED utils.cpp)
#target_link_libraries(utils INTERFACE boost_regex)
target_link_libraries(utils INTERFACE boost_regex)
target_link_libraries(utils INTERFACE "-Wl,-rpath,${Boost_LIBRARY_DIRS}")

install(TARGETS utils
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ)
