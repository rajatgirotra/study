# set or default build type in CMake cache
if (NOT CMAKE_BUILD_TYPE AND CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()

message(STATUS "Setting build type to ${CMAKE_BUILD_TYPE}")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

# ccache is a compiler cache.
# if ccache is found, the makefile generators will call this tool and pass the compiler and its arguments
# to this tool. setting the CMAKE_CXX_COMPILER_LAUNCHER will set the property <LANG>_COMPILER_LAUNCHER
# TODO evaluate distcc vs ccache at some later stage.
find_program(CCACHE ccache)
if(CCACHE)
    message(STATUS "found ccache - ${CCACHE}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
    message("ccache not found, cannot use")
endif()

# generate compile_commands.json during build time. this file is useful when working with certain
# clang based compilers. example, vim YCM (YouCompleteMe) can leverage compiler_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# check if compiler supports LTO (link time optimization)
# Pass "-DENABLE_LTO=ON" to cmake to enable LTO. If compiler doesnt support LTO
# log error, but continue anyway.
option(ENABLE_LTO "Enable if compiler supports link time optimization" ON)
if(ENABLE_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        message(NOTICE "LTO (link time optimization) is enabled.")
    else()
        message(SEND_ERROR "LTO (link time optimization) is not supported: ${output}.")
    endif()
else()
    message(NOTICE "LTO (link time optimization) is disabled.")
endif()
