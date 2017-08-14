
add_executable(main main.cpp)
target_link_libraries(main PRIVATE utils)

install(TARGETS main
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ)
