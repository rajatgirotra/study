function(set_project_warnings warnings)
    # treat warnings as errors?
    option(WARNINGS_AS_ERRORS "treat compiler warnings as errors" ON)
    set(GCC_WARNINGS
            -Wall
            -Wextra # reasonable and standard
            -Wshadow # warn the user if a variable declaration shadows one from a parent context
            -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
            -Wold-style-cast # warn for c-style casts
            -Wcast-align # warn for potential performance problem casts
            -Wunused # warn on anything being unused
            -Woverloaded-virtual # warn if you overload (not override) a virtual function
            -Wpedantic # warn if non-standard C++ is used
            -Wno-conversion # warn on type conversions that may lose data
            -Wno-sign-conversion # warn on sign conversions
            -Wnull-dereference # warn if a null dereference is detected
            -Wduplicated-cond # warn when if/else branches have duplicated conditions
            -Wduplicated-branches # warn when if/else branches have duplicated code
            -Wlogical-op # warn bout logical operations being used where bitwise were probably wanted.
            -Wuseless-cast # warn if your perform a cast to the same type
            -Wdouble-promotion # warn if float is implicit promoted to double
            -Wdeprecated-declarations
            -Wformat=2 # warn on security issues around functions that format output
            -fconcepts-diagnostics-depth=2
            -Wno-sign-compare
            -Wno-overflow
            # (ie printf)
            )

    if(WARNINGS_AS_ERRORS)
        set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
    endif()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    else()
        message(AUTHOR_WARNING "no compiler warnings enables for ${CMAKE_CXX_COMPILER_ID} compiler")
    endif()

    # set warnings finally
    target_compile_options(${warnings} INTERFACE ${PROJECT_WARNINGS})
endfunction()
