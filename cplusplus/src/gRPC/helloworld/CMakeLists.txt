get_filename_component(hw_proto "../protos/helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)
#message(STATUS ${hw_proto})
#message(STATUS ${hw_proto_path})

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")

# custom command to run protoc compiler
add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grps_hdrs}"
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        #        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN_PROGRAM}"
        "${hw_proto}"
        DEPENDS "${hw_proto}"
)

add_library(hw_grpc_proto ${hw_proto_srcs} ${hw_grpc_srcs})
target_include_directories(hw_grpc_proto PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(hw_grpc_proto PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings)
target_link_libraries(hw_grpc_proto PUBLIC grpc::grpc)

add_executable(grpc_greeter_client greeter_client.cpp)
target_link_libraries(grpc_greeter_client PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings hw_grpc_proto absl::flags_parse)

add_executable(grpc_greeter_server greeter_server.cpp)
target_link_libraries(grpc_greeter_server PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings hw_grpc_proto absl::flags_parse)

add_executable(grpc_greeter_callback_client greeter_callback_client.cpp)
target_link_libraries(grpc_greeter_callback_client PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings hw_grpc_proto absl::flags_parse)

add_executable(grpc_greeter_callback_server greeter_callback_server.cpp)
target_link_libraries(grpc_greeter_callback_server PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings hw_grpc_proto absl::flags_parse)

add_executable(grpc_greeter_async_client greeter_async_client.cpp)
target_link_libraries(grpc_greeter_async_client PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings hw_grpc_proto absl::flags_parse)

add_executable(grpc_greeter_async_client2 greeter_async_client2.cpp)
target_link_libraries(grpc_greeter_async_client2 PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings hw_grpc_proto absl::flags_parse)

add_executable(grpc_greeter_async_server greeter_async_server.cpp)
target_link_libraries(grpc_greeter_async_server PRIVATE ${PROJECT_NAME_LOWERCASE}_project_options  ${PROJECT_NAME_LOWERCASE}_project_warnings hw_grpc_proto absl::flags_parse)

get_filename_component(rr_proto "protos/record_route.proto" ABSOLUTE)
get_filename_component(rr_proto_path "${rr_proto}" PATH)
