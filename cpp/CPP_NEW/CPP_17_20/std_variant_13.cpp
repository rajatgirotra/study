/*
 * You can only compare two variants of the same type
 * 1) If they same alternative is active in both variants, its comparison operator is called.
 * 2) If one variant has an "earlier" alternative set, then it is less than the other variant.
 *
 * Variants are moveable.
 *
 * std::hash on variant is defined if and only if std::hash on each of its alternative is defined, otherwise it is poisoned.
 *
 * bool valueless_by_exception() --> This returns true if the variant is in an error state. This can happen when you are changing the alternate in the variant.
 * When a variant is valueless_by_exception(), the index() function returns variant::npos, and the std::get(), std:::visit() etc will throw bad_variant_access.
 */

#include <iostream>
#include <string>
#include <variant>
#include <cxxabi.h>
#include <cassert>
#include <typeinfo>

using namespace std;
namespace {
    [[maybe_unused]] string demangle(const char* mangled_name) {
        int result {-1};
        auto demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &result);
        assert(result == 0);
        string name(demangled_name);
        free(demangled_name);
        return name;
    }
}

struct ThrowingClass {
    int m_val;
    ThrowingClass(int arg) : m_val(arg) {
        if (m_val == 0)
            throw int();
    }

    operator int() { throw int(); }
};

int main() {
    std::variant<int, ThrowingClass> v; // by default alternative will be int

    try {
        v = ThrowingClass(0); // will throw.
    } catch(...) {
        // since the c'tor itself throws, the old variant value is not destroyed yet.
        // the sequence is 1) Create new object, destroy old object, assign new alternative to variant
        cout << "valueless_by_exception:  " << v.valueless_by_exception() <<", index: " << v.index() << endl;
    }

    try {
         v.emplace<0>(ThrowingClass(10)); // the ctor doesn't throw, but the converting member function throws.
    } catch(...) {
        cout << "valueless_by_exception:  " << v.valueless_by_exception() <<", index: " << v.index() << endl;
    }

}

/*
 * Uses of std::variant<>
 * 1) May be to parse config options from a config file. The config values could be integer, double, string and we could have a variant
 * for it. The parse() method would try to parse the value as float, if that fails, try to parse as integer otherwise
 * assume it's a string.
 *
 * 2) The function return type could be a variant<ActualReturnType, ErrorCode> where ErrorCode is some enum.
 *
 * 3) To create a finite state machine where variant<> is used to store the states.
 * std::variant<DoorOpened, DoorClosed, DoorLocked> where states are simple classes like struct DoorOpened{}; struct DoorLocked{}; etc.
 * DoorClosed{};
 * and we could define visitor classes accordingly, which will be like Event's which happen
 *
 * 4)
 */
