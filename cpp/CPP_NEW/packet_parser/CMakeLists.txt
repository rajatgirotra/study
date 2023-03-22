add_library(parser STATIC
        Encoder.cpp
        Decoder.cpp
        InputFormat.cpp
        OutputFormat.cpp
        Processor.cpp
        Parser.cpp)

add_executable(Solution main.cpp)
target_link_libraries(Solution PRIVATE parser)
