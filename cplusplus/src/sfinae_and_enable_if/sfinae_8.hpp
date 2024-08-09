#pragma once


#include <type_traits>
#include <utility>
#include <string>
using std::string;

template <typename T>
struct hasSerialize {
private:
    template <typename U>
    static constexpr bool test(...) { return false; }

/*
    template <typename U>
    static constexpr auto test(int) -> decltype(std::declval<U>().serialize(), bool()) { return true;} // C++11
*/

    template <typename U>
    static constexpr decltype(std::declval<U>().serialize(), bool()) test(int)  { return true;} // C++14

public:
    static constexpr bool value = (test<T>(int()) == true);
};

template <typename T, typename std::enable_if<hasSerialize<T>::value>::type* = nullptr>
string serialize(const T& t) {
    return t.serialize();
}

template <typename T, typename std::enable_if<!hasSerialize<T>::value>::type* = nullptr>
string serialize(const T& t) {
    return to_string(t);
}

