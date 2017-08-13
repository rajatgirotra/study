include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
set(TEMP_DIR "${CMAKE_BINARY_DIR}/temp")

# check if compiler supports C++11/14/17
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0x)

if (COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0x)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different compiler.")
endif()


# check if compiler supports override keyword
file(WRITE ${TEMP_DIR}/TestOverride.cpp
        "struct Base { virtual ~Base(){}; virtual void test(); };\n
         struct Derived : Base { void test() override {} };\n
         int main() { return 0;}")

try_compile(HAS_OVERRIDE ${TEMP_DIR} ${TEMP_DIR}/TestOverride.cpp)
if(NOT HAS_OVERRIDE)
    message(FATAL_ERROR "${PROJECT_NAME} needs a C++ compiler with support for 'override'")
endif()


# Check compiler has atomics
CHECK_INCLUDE_FILE_CXX(atomic HAS_ATOMIC)
if (NOT HAS_ATOMIC)
    message(FATAL_ERROR "${PROJECT_NAME} needs a C++ compiler with <atomic>")
endif()

# Just like above we can add more things here like emplace support, HAS_UNORDERED_MAP etc.