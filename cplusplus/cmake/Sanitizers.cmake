function(enable_sanitizers project_options)
    # TODO check gcc --coverage flag and how it is used and try to integrate here.

    # currently sanitizer support is provided by GNU and Clang compilers
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        set(SANITIZERS "")

        # Enable/Disable ThreadSanitizer, a fast data race detector. Cannot be combined with AddressSanitizer
        option(ENABLE_SANITIZER_THREAD "enable thread sanitizer" OFF)
        if(ENABLE_SANITIZER_THREAD)
            list(APPEND SANITIZERS "thread")
        endif()

        # Enable/Disable AddressSanitizer, a fast memory error detector. Cannot be combined with ThreadSanitizer
        option(ENABLE_SANITIZER_ADDRESS "enable address sanitizer" OFF)
        if(ENABLE_SANITIZER_ADDRESS)
            list(APPEND SANITIZERS "address")
        endif()

        # Enable/Disable LeakSanitizer, a fast memory leak detector. Cannot be combined with ThreadSanitizer
        option(ENABLE_SANITIZER_MEMORY_LEAK "enable memory leak sanitizer" OFF)
        if(ENABLE_SANITIZER_MEMORY_LEAK)
            list(APPEND SANITIZERS "leak")
        endif()

        # Enable/Disable UndefinedBehaviorSanitizer, a fast undefined behavior detector.
        option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "enable undefined behavior sanitizer" OFF)
        if(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
            list(APPEND SANITIZERS "undefined")
        endif()

        list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)
    endif()

    if(LIST_OF_SANITIZERS)
        # check if any sanitizer is enabled
        if(NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
            target_compile_options(${project_options} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
            target_link_libraries(${project_options} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
        endif()
    endif()

endfunction()