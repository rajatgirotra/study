add_library(Square)
target_sources(Square
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        mod0.cppm
)
