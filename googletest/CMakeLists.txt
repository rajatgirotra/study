cmake_minimum_required(VERSION 3.10)
project(soundex VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH /home/rajatgirotra/tools/miniconda2/envs/gcc73)
option(UNITTESTS "Build Unittests" ON)
message(STATUS "Build Unittests: ${UNITTESTS}")
include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)
if(UNITTESTS)
    include(CTest)
    enable_testing() # allows you to run "make test"
    find_package(GTest REQUIRED)
    include(GoogleTest)
    if(NOT GTEST_FOUND)
        message(FATAL_ERROR "Dependency GTest not found")
    endif()
    message(STATUS "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
    get_filename_component(GTEST_ROOT ${GTEST_INCLUDE_DIRS} DIRECTORY)
    set(GTEST_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_ROOT}/lib/libgmock.a)
    message(STATUS "GTEST_LIBRARIES: ${GTEST_LIBRARIES}")

    add_subdirectory(tests)
endif()

