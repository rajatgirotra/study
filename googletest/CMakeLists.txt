cmake_minimum_required(VERSION 3.9)
project(googletest VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /home/rajatgirotra/tools/miniconda2/envs/shriram)
option(UNITTESTS "Build Unit Tests.." ON)
include(CTest)

message(STATUS "UNITTESTS: ${UNITTESTS}")
if(UNITTESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    if(NOT GTEST_FOUND)
        message(FATAL_ERROR "No GoogleTest/GoogleMock installation found. Cannot build Unittests")
    else()
        message(STATUS "GoogleTest include path: " ${GTEST_INCLUDE_DIRS})
        message(STATUS "GoogleTest libraries: " ${GTEST_LIBRARIES})
        get_filename_component(GTEST_ROOT ${GTEST_LIBRARIES} DIRECTORY)
        set(GMOCK_LIBRARIES ${GTEST_ROOT}/libgmock.a)
        message(STATUS "GoogleMock libraries: " ${GMOCK_LIBRARIES})
    endif()
    add_subdirectory(c2)

endif()

