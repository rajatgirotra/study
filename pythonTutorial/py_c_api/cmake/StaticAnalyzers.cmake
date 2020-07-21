option(ENABLE_CPPCHECK "enable static code analysis with cppcheck." OFF)
option(ENABLE_CLANG_TIDY "enable static code analysis with clang-tidy." OFF)

if(ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck HINTS ${DEVTOOLS_DIR})
    if(CPPCHECK)
        # setting CMAKE_CXX_CPPCHECK will enable CXX_CPPCHECK target property on all targets.
        # this will make cmake run cppcheck on all targets during compilation and report any problems.
        message(STATUS "found cppcheck - ${CPPCHECK}")
        set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --suppress=missingInclude --enable=all --inconclusive)
    else()
        message(SEND_ERROR "cppcheck requested but not executable not found")
    endif()
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy) # no hint needed as llvm tools are already in environment
    if(CLANGTIDY)
        # setting CMAKE_CXX_CLANG_TIDY will enable CXX_CLANG_TIDY target property on all targets.
        # this will make cmake run cppcheck on all targets during compilation and report any problems.
        message(STATUS "found clang-tidy - ${CLANGTIDY}")
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    else()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()