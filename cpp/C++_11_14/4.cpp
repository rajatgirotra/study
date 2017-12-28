/*
 * Very good example to remove any confusion on whether an auto keyword will resolve to a value type or a reference type.
 * The rule is simple, it is just how you define it. Eg:
 * int i = 5;
 * auto a1 = i; //value
 * auto& a2 = i; //reference.
 */

#include <iostream>
#include <cxxabi.h>
#include <string>
#include <cassert>
using std::cout;
using std::endl;
using std::string;

string demangle(const char* mangled_name) {
    auto status {0};
    auto realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    assert(status == 0 && realname != nullptr);
    return realname;
}

template<typename T>
struct A {
	static void foo() {
		cout << "value type: " << demangle(typeid(T).name()) << endl;
	}
};

//template partialization
template <typename T>
struct A <T&> {
	static void foo() {
		cout << "reference type: " << demangle(typeid(T).name()) << endl;
	}
};

float& bar() {
	static float f = 5.5;
	return f;
}

int main() {
	int i = 5;
	int& r = i;

	auto a1 = i;
	auto a2 = r;
	auto a3 = bar();

	A<decltype(i)>::foo(); //value
	A<decltype(r)>::foo(); //reference
	A<decltype(a1)>::foo(); //value
	A<decltype(a2)>::foo(); //value
	A<decltype(bar())>::foo(); //reference
	A<decltype(a3)>::foo(); //value

	return 0;
}

	
	
// note that cxxabi only gives you the type. It doesnt tell you if T is a value_type of reference_type. So T or T& or T&& will only give the same type.	
