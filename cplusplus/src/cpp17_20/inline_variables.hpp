/*
 * inline variables. You already know that class member functions defined inside the body of the class itself are implicitly inline.
 * Also class member functions defined in the header file itself and outside the class body must be declared as INLINE. this inline
 * is to tell the compiler that multiple translation units may include the header file, so you may find the same function defined over and over
 * but just treat them as one function.
 *
 * Same can now be done for class static member variables (const or non-const).
 * A static member variable declared inline has the same semantics as a function declared inline: it can be defined, identically, in multiple
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

/* let's include this header both in inline_function.cpp and inline_functions_16.cpp and see that there are no compiler and linker errors.
    One more thing, in C++17, constexpr static data members are inline by default. That means we can omit out the line of definition of static constexpr variables, but not static const.
	
 */
 
 /*
 In C++11, 
 1) non-static data members of any type,
 2) static constexpr data members of any type,
 3) and static const data members of integral or enumeration type may be initialized in the class declaration. e.g.

   struct X {
      int i=5;  --> 1)
      const float f=3.12f;  --> 1)
      static const int j=42; --> 3)
      static constexpr float g=9.5f; --> 2)
    };
	
Since float and double are not of integral or enumeration type, such members must either be constexpr,
or non-static in order for the initializer in the class definition to be permitted.

Prior to C++11, only static const data members of integral or enumeration type could have initializers in the class definition.
i.e only 3) was allowed.

Also if:

In first.hpp
template<typename T>
struct cond_I
{ static constexpr T value = 0; }; 


// specialization 
template<typename T>
struct cond_I< std::complex<T> >
{ static constexpr std::complex<T> value = {0,1}; }; 

in main.cpp
cout << cond_I<double>::value << endl;            // this works fine
cout << cond_I< complex<double> >::value << endl; // linker error ?? with C++11 and C++14, not with C++17.

linker error with C++11 and C++14 is because the ostream operator for std::complex<> takes the std::complex<> by reference. and that is
considered odr-used. and for odr-used we must provide a definition.
ostream::operator<<(ostream&, const complex<T> &) --> odr-used
ostream::operator<<(ostream&, double); --> not odr-used

with C++17, static constexpr is implicitly inline by default, so we dont need a definition.

Also if we change static constexpr to static const, we get an error: as you read above only static const integral and enumeration types can have in class initializer. So here we have type T and type complex<>; both of which are not integral.


*/
