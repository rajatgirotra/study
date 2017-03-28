/*
 * Now that you know about cstdint, write a program that gives the smallest type that is required to fit a given integer. For example.
 * IntTypeThatFits(0) returns int8_t.
 * IntTypeThatFits(127) returns int8_t.
 * IntTypeThatFits(128) returns int16_t.
 * IntTypeThatFits(32768) returns int32_t.
 */

#include <iostream>
#include <cstdint>
#include <limits>
#include <typeinfo>
using namespace std;

template <bool fits8, bool fits16, bool fits32>
struct IntTypeThatFitsHelper {
};

template <>
struct IntTypeThatFitsHelper<true, true, true> {
	typedef int8_t Result;
};

template <>
struct IntTypeThatFitsHelper<false, true, true> {
	typedef int16_t Result;
};

template <>
struct IntTypeThatFitsHelper<false, false, true> {
	typedef int32_t Result;
};

template <>
struct IntTypeThatFitsHelper<false, false, false> {
	typedef int64_t Result;
};

template <int64_t n>
struct IntTypeThatFits {
	typedef typename IntTypeThatFitsHelper<
		(n <= numeric_limits<int8_t>::max()) && (n >= numeric_limits<int8_t>::min()),
		(n <= numeric_limits<int16_t>::max()) && (n >= numeric_limits<int16_t>::min()),
		(n <= numeric_limits<int32_t>::max()) && (n >= numeric_limits<int32_t>::min())
	>::Result Result;
};

int main() {
	IntTypeThatFits<10>::Result a = 10;
	IntTypeThatFits<256>::Result b = 256;
	IntTypeThatFits<32768>::Result c = 32768;
	cout << "type of a: " << typeid(a).name() << endl;
	cout << "type of b: " << typeid(b).name() << endl;
	cout << "type of c: " << typeid(c).name() << endl;
}

