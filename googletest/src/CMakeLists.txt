add_library(soundex_algo SHARED soundex.cpp)
add_executable(soundex main.cpp)
target_link_libraries(soundex PUBLIC soundex_algo)