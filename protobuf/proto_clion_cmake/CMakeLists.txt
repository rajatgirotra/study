cmake_minimum_required(VERSION 3.9)

project(proto_cmake VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_PREFIX_PATH /home/rajatgirotra/tools/miniconda2/envs/shriram)
find_package(Protobuf REQUIRED)
message(STATUS "Found Protobuf version ${Protobuf_VERSION}")
message(STATUS "Protobuf include dir is ${Protobuf_INCLUDE_DIRS}")
message(STATUS "Protobuf libraries are ${Protobuf_LIBRARIES}")

include_directories(${Protobuf_INCLUDE_DIRS})

add_subdirectory(protos)
add_subdirectory(src)
