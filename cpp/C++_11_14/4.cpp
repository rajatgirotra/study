/*
 * Very good example to remove any confusion on whether an auto keyword will resolve to a value type or a reference type.
 * The rule is simple, it is just how you define it. Eg:
 * int i = 5;
 * auto a1 = i; //value
 * auto& a2 = i; //reference.
 */

#include <iostream>
using std::cout;
using std::endl;

template<typename T>
struct A {
	static void foo() {
		cout << "value" << endl;
	}
};

//template partialization
template <typename T>
struct A <T&> {
	static void foo() {
		cout << "reference" << endl;
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

	
	
	
