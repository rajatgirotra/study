add_library(utils SHARED utils.cpp)
#target_link_libraries(utils INTERFACE boost_regex)
target_link_libraries(utils INTERFACE boost_regex)
target_link_libraries(utils INTERFACE "-Wl,-rpath,${Boost_LIBRARY_DIRS}")

install(TARGETS utils
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ)

set (_resolvedFiles "")
file(GLOB BOOST_DEPS LIST_DIRECTORIES false "${Boost_LIBRARY_DIRS}/libboost*.so.*")
#message(STATUS "${BOOST_DEPS}")
foreach (_file ${BOOST_DEPS})
    get_filename_component(_resolvedFile "${_file}" REALPATH)
    #message(STATUS "${_file}")
    list (APPEND _resolvedFiles "${_resolvedFile}")
endforeach()

install(FILES ${_resolvedFiles}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ)