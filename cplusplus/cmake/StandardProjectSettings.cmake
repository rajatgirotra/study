message(STATUS "Building with cmake version ${CMAKE_VERSION}")

# enable ccache if available
include(${CMAKE_CURRENT_LIST_DIR}/ccache.cmake)
enable_ccache(PROGRAM ccache QUIET BASE_DIR ${CMAKE_SOURCE_DIR})

# generate compile_commands.json during build time. this is useful when working with certain clang based compilers.
# also vim YCM (YouCompleteMe) can leverage compiler_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set CMAKE_INSTALL_RPATH
set(CMAKE_INSTALL_RPATH "$ORIGIN/../hotfix:$ORIGIN/../lib")

# check if compiler supports LTO (link time optimization)
# Pass "-DENABLE_LTO=ON" to cmake to enable LTO. If compiler doesnt support LTO
# log error, but continue anyway.
option(ENABLE_LTO "Enable if compiler supports link time optimization" OFF)
if(ENABLE_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        message(NOTICE "LTO (link time optimization) is enabled.")
        add_compile_options(-flto)
    else()
        message(SEND_ERROR "LTO (link time optimization) is not supported: ${output}.")
        add_compile_options(-fno-lto)
    endif()
else()
    message(NOTICE "LTO (link time optimization) is disabled.")
    add_compile_options(-fno-lto)
endif()

message(STATUS "CMAKE_INSTALL_PREFIX is ${CMAKE_INSTALL_PREFIX}")
include(GNUInstallDirs)