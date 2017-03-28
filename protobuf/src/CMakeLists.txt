cmake_minimum_required(VERSION 3.5.0)

project(PROTOBUF_STUDY VERSION 1.0.0 LANGUAGES C CXX)

# Find protobuf first
find_package(Protobuf REQUIRED)
if (NOT ${PROTOBUF_FOUND})
  message(FATAL_ERROR "Google protobuf not found")
endif()

add_subdirectory(proto)

message("Address Book Source Proto is " ${ADDRESSBOOK_SRC_PROTO})
add_executable(addressbook ${ADDRESSBOOK_SRC_PROTO} addressbook.cpp)
set_source_files_properties(${ADDRESSBOOK_SRC_PROTO} PROPERTIES GENERATED TRUE)
target_include_directories(addressbook SYSTEM PRIVATE ${CMAKE_BINARY_DIR}/proto ${PROTOBUF_INCLUDE_DIRS})
target_compile_options(addressbook PRIVATE -std=gnu++1y -Wabi-tag)
target_compile_definitions(addressbook PRIVATE -D_GLIBCXX_USE_CXX11_ABI=0)
target_link_libraries(addressbook ${PROTOBUF_LIBRARIES})
add_dependencies(addressbook generated_code)



#   find_package(Protobuf REQUIRED)
#   include_directories(${PROTOBUF_INCLUDE_DIRS})
#   include_directories(${CMAKE_CURRENT_BINARY_DIR})
#   protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS foo.proto)
#   protobuf_generate_python(PROTO_PY foo.proto)
#   add_executable(bar bar.cc ${PROTO_SRCS} ${PROTO_HDRS})
#   target_link_libraries(bar ${PROTOBUF_LIBRARIES})
