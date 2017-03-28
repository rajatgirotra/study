/*
polymorphic_cast is just like C++ dynamic_cast with the exception that it will always throw an std::bad_cast exception.
Remember that dynamic_cast throws an exception only when using reference types. It returns a NULL pointer when using pointers.

It is defined as a function in boost/cast.hpp

template <typename Target, typename Source>
polymorphic_cast(Source* p);

IT CAN ALSO BE OVERLOADED AS DESIRED.
*/

#include <iostream>
#include <boost/cast.hpp>
using namespace std;

class base1 {
public:
	virtual void print() {
		cout << "base1::print() " << endl;
	}

	virtual ~base1() { }
};

class base2 {
public:
	void only_base2() {
		cout << "base2::only_base2()" << endl;
	}

	virtual ~base2() { }
};

class derived : public base1, public base2 {
public:
	void only_here() {
		cout << "derived::only_here()" << endl;
	}

	void only_base2() {
		cout << "derived::only_base2() " << endl;
	}
};

int main() {
	base1* p1 = new derived;

	//Works without any cast
	p1->print();

	try {
		//Downcast
		derived* pD = boost::polymorphic_cast<derived*>(p1);
		pD->only_here();
		pD->only_base2();

		//Crosscast to get a pointer to base2 from base1
		base2* pB = boost::polymorphic_cast<base2*>(p1);
		pB->only_base2();

		//demonstrate failure of polymorphic_cast
		pB = new base2;
		base1* pB1 = boost::polymorphic_cast<base1*>(pB);

	}catch(std::bad_cast& e) {
		cout << e.what() << endl;
	}

	delete p1;
	return 0;
}

/*

Use polymorphic_cast when a failed cast is a dire error. i.e you can do nothing more than throwing an exception and just quitting.
If a failed polymorphic_cast is not a very serious error and can be expected in certain cases, consider using dynamic_cast.

*/
