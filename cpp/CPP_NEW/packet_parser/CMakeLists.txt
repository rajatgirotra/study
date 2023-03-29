add_library(parser STATIC
        src/Encoder.cpp
        src/Decoder.cpp
        src/InputFormat.cpp
        src/OutputFormat.cpp
        src/Processor.cpp
        src/OrderManager.cpp
        src/Parser.cpp)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Solution src/main.cpp)
target_link_libraries(Solution PRIVATE parser)
