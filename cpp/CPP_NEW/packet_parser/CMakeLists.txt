add_library(parser STATIC Parser.cpp DecoderUtils.cpp Processor.cpp InputFormat.cpp)

add_executable(Solution main.cpp)
target_link_libraries(Solution PRIVATE parser)
