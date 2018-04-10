file(GLOB ALL_PROTOS LIST_DIRECTORIES FALSE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.proto)
protobuf_generate_cpp(CPP_SRCS CPP_HDRS ${ALL_PROTOS})
protobuf_generate_python(PY_SRCS ${ALL_PROTOS})

add_library(common_proto SHARED ${CPP_SRCS} ${CPP_HDRS})
target_link_libraries(common_proto INTERFACE "-Wl,-rpath,/home/rajatgirotra/tools/miniconda2/envs/shriram/lib")
target_link_libraries(common_proto INTERFACE ${Protobuf_LIBRARIES})
