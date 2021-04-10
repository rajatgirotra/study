/*
 * inline variables. You already know that class member functions defined inside the body of the class itself are implicitly inline.
 * Also class member functions defined in the header file itself and outside the class body must be declared as INLINE. this inline
 * is to tell the compiler that multiple translation units may include the header file, so you may find the same function defined over and over
 * but just treat them as one function.
 *
 * Same can now be done for class static member variables (const or non-const).
 * A variable declared inline has the same semantics as a function declared inline: it can be defined, identically, in multiple
 * translation units, must be defined in every translation unit in which it is used, and the behaviour of the program is as if
 * there was exactly one variable.
 */

#include <random>

struct X {
    // 1st way. define inline outside the class body in the header file.
    static int m_tag;

    // 2nd way. define inline inside the class body itself.
    inline static int m_tag_2 {-99};

    // 3rd. inline static const member with random value initialized with rand() will have the same random value
    // across all translation units. C++ guarantees that.
    inline static const int m_random_value = rand();

};

inline int X::m_tag {100};

/* lets include this header both in inline_function.cpp and inline_functions_16.cpp and see that there are no compiler and linker errors. */