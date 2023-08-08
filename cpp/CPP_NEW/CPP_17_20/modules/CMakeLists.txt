add_library(Square)
target_sources(Square
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        mod0.cppm
)

add_executable(mod0main mod0main.cpp)
target_link_libraries(mod0main PRIVATE Square)