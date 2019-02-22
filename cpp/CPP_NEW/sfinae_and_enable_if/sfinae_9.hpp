#pragma once


#include <type_traits>
#include <utility>
#include <string>
using std::string;

template <typename T, typename = string>
struct hasSerialize : std::false_type {};

template <typename T>
struct hasSerialize<T, decltype(std::declval<T>().serialize())> : std::true_type {};

template <typename T, typename std::enable_if<hasSerialize<T>::value>::type* = nullptr>
string serialize(const T& t) {
    return t.serialize();
}

template <typename T, typename std::enable_if<!hasSerialize<T>::value>::type* = nullptr>
string serialize(const T& t) {
    return to_string(t);
}

