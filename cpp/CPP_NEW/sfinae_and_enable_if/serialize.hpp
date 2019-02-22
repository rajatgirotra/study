#pragma once

#include <string>
using std::string;

struct A {};

string to_string(const A&) {
    return "I am A";
}

struct B {
    string serialize() const {
        return "I am B";
    }
};

struct C {};

string to_string(const C&) {
    return "I am C";
}

#if (VERSION == 1)
   #include "sfinae_7.hpp"
#elif (VERSION == 2)
   #include "sfinae_8.hpp"
#else
   #include "sfinae_9.hpp"
#endif
