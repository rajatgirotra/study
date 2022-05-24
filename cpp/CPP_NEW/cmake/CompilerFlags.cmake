function(set_project_flags compile_flags)
    set(GCC_COMPILE_FLAGS
            # Optimize debugging experience. ‘-Og’ should be the optimization level of choice for the standard edit-compile-debug cycle,
            # offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.
            # It is a better choice than ‘-O0’ for producing debuggable code because some compiler passes that collect debug
            # information are disabled at ‘-O0’.
            -Og
            )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(PROJECT_COMPILE_FLAGS ${GCC_COMPILE_FLAGS})
    else()
        message(AUTHOR_WARNING "no compiler flags found for ${CMAKE_CXX_COMPILER_ID} compiler")
    endif()

    # set compile flags
    target_compile_options(${compile_flags} INTERFACE ${PROJECT_COMPILE_FLAGS})
endfunction()
