/*
constinit = constexpr - const
constinit is applied to global or static variables. It is a way for the compiler to force that a static or global variable is initialized at compile time.
The value itself is not const, and can be modified at runtime. That's why we say it is constexpr - const.

A constexpr expression can be used to initialize a constinit value. But a constinit variable cannot be used to initialize another constinit as constinit
is not really a constant expression. A constinit variable which is thread_local storage can improve performance, as compiler need not put a check to validate if the
variable is initialized or not.

constinit and constexpr together can also be used to solve the "static initialization order fiasco" problem.

consteval is applied to a function and force the compiler to evaluate it compile time only. It is also called as an immediate function. this kind of function cannot
be called at run time. basically, functions can be:

neither constexpr nor consteval --> i.e. they can be used at run time only.
constexpr --> i.e. they can be used at both compile time and run time.
consteval --> i.e. they can only be used at compile time only.

Even lambda can be consteval. Note that all arguments to consteval function should also be literals or constexpr variables.
consteval functions MUST ALSO BE USED IN A COMPILE TIME CONTEXT.
Also, all statements in a consteval function must also be usable in a constant context.
 */

#include <iostream>
#include <string>
#include <cstdint>
#include <utility>
#include <array>
#include <iterator>
#include <list>
#include <ranges>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <type_traits>

using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

constinit auto i = 42;

int getNextClassId() {
    static constinit int maxId = 0;
    return ++maxId;
}

class MyType {
    static inline constinit long max = sizeof(int) * 1000;
};

constexpr std::array<int, 5> getColl() {
    return {1, 2, 3, 4, 5};
}

constinit auto globalColl = getColl(); // getColl() must be a constexpr function

[[maybe_unused]] static thread_local constinit int numCalls = 0;
// better performance as compiler does not use an internal guard

constinit std::pair p{42, "ok"};
// constinit std::list<int> l; // error: 'constinit' variable 'l' does not have a constant initializer

// If you have an "extern constinit int max"; in header file and "constinit int max = 42;" in source file, the "constinit" is optional in header file,
// but cannot be omitted in source file.


// a consteval lambda to calculate the hash of certain string literals.
auto hashed = [](const char *ptr) consteval {
    std::size_t hash = 5381;
    while (*ptr != '\0') {
        hash = hash * 33 ^ *ptr++;
    }
    return hash;
};

void compileTimeError() {
}

consteval int nextTwoDigitValue(int val) {
    if (val < 0 || val >= 99) {
        compileTimeError();
        // this is ok as long as this code is not reached (same rule also applies to constexpr functions at compile time).
    }
    return ++val;
}

// Note that using static_assert() would not work here because it can only be called for values known at
// compile time and consteval does not make val a compile-time value inside the function:
consteval int nextTwoDigitValue2(int val) {
    static_assert(val >= 0 && val < 99);
    // always ERROR: val is not a compile-time value
}

constexpr int mystrlen(const char* s)
{
    // new helper function to chose between compile time vs run time implementation.
    // based on the context in which the len() function is called.
    if (std::is_constant_evaluated()) {
        int idx = 0;
        while (s[idx] != '\0') {
            // compile-time friendly code
            ++idx;
        }
        return idx;
    }
    else {
        return std::strlen(s);
        // function called at runtime
    }
}

int main() {
    // OK (requires hashed() in compile-time context):
    enum class drinkHashes : long {
        beer = hashed("beer"), wine = hashed("wine"),
        water = hashed("water")
    };

    // OK (hashed() guaranteed to be called at compile time):
    [[maybe_unused]] std::array arr{hashed("beer"), hashed("wine"), hashed("water")};

    constexpr int l1 = mystrlen("hello"); // uses if branch
    int l2 = mystrlen("hello"); // uses else branch (no required compile-time context)
}
