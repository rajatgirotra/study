/*
 * C++0x11 reuses the auto keyword to infer the type of the variable from its initializer.
 */

#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;

int main() {
	auto x = 5; //x will be of type int
	auto y = 5.5; //y will be double
	auto z = y; //z will be of type double.
	auto a = "Hello"; //a will be const char*
	auto d = {1, 2};
        auto x2 = x;
        ++x2;

	cout << "x = " << x << "  of type: " << typeid(x).name() << endl;
	cout << "x2 = " << x2 << "  of type: " << typeid(x2).name() << endl;
	cout << "y = " << y << "  of type: " << typeid(y).name()<< endl;
	cout << "z = " << z << "  of type: " << typeid(z).name() << endl;
	cout << "a = " << a << "  of type: " << typeid(a).name() << endl;
	cout << "d of type: " << typeid(d).name() << endl;

	//auto p; //Error. Cant declare an auto variable without an initialiser.

	return 0;
}

/*
 * Output
 *
 * x = 5  of type: i
 * y = 5.5  of type: d
 * z = 5.5  of type: d
 * a = Hello  of type: PKc
 * d of type: St16initializer_listIiE
 */
