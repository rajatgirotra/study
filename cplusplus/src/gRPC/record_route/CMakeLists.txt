get_filename_component(rr_proto "../protos/route_guide.proto" ABSOLUTE)
get_filename_component(rr_proto_path "${rr_proto}" PATH)

# Generated sources
set(rr_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.pb.cc")
set(rr_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.pb.h")
set(rr_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.grpc.pb.cc")
set(rr_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.grpc.pb.h")

add_custom_command(OUTPUT "${rr_proto_srcs}" "${rr_grpc_srcs}" "${rr_proto_hdrs}" "${rr_grpc_hdrs}"
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rr_proto_path}"
        --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN_PROGRAM}"
        "${rr_proto}"
        DEPENDS "${rr_proto}"
)

add_library(rr_grpc_proto ${rr_proto_srcs} ${rr_grpc_srcs})
target_include_directories(rr_grpc_proto PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(rr_grpc_proto PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_link_libraries(rr_grpc_proto PUBLIC grpc::grpc)

add_executable(rr_grpc_server route_guide_server.cpp helper.cpp)
target_include_directories(rr_grpc_server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(rr_grpc_server PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings rr_grpc_proto absl::flags_parse)