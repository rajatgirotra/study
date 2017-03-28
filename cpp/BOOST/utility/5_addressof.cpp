/*
Boost defines a template function "addressof" which returns the address of the actual object being pointed to. 
The thing to know is that even if you overload the address-of operator for your class to return something nasty. address will still return you the actual address of the object. It does so by bpassing the overloaded & and by applying some hacks.

template <typename T>
inline T* addressof(const T& t) {
	return (actual address of t);
}

eg below:
*/

#include <iostream>
#include <boost/utility.hpp>
using namespace std;

template <typename T>
inline T* print_address_of(const T& t) {
	cout << "&t = " << &t << endl;
	cout <<"boost::addressof(t) = "<< boost::addressof(t) << endl;
}

class MyClass {
public:
	int operator&() const {
		return 13;
	}
};

int main() {
	MyClass o;
	print_address_of(o);

	return 0;
}
