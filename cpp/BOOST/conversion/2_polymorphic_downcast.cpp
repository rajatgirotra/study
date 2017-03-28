/*
Sometimes dynamic_cast is considered too inefficient (measured, I'm sure!). There is runtime overhead for performing dynamic_casts. To avoid that overhead, it is tempting to use static_cast, which doesn't have such performance implications. static_cast for downcasts can be dangerous and cause errors, but it is faster than dynamic_cast. If the extra speed is required, we must make sure that the downcasts are safe. static_cast just performs the necessary pointer arithmetic and leaves it up to the programmer to make sure that the conversion is valid. 

polymorphic_downcast tests the cast with dynamic_cast, but only in debug builds; it then uses static_cast to perform the conversion. In release mode, only the static_cast is performed. The nature of the cast implies that you know it can't possibly fail, so there is no error handling, and no exception is ever thrown. So what happens if a polymorphic_downcast fails in a non-debug build? Undefined behavior.

polymorphic_downcast is used in situations where you'd normally use dynamic_cast but don't because you're sure which conversions will take place, that they will all succeed, and that you need the improved performance it brings. 

i.e.

in DBEUG BUILDS - polymorphic_downcast tests the cast with dynamic_cast, if successfull uses static_cast to perform the cast, else with raise an assertion.
in RELEASE BUILDS - polymorphic_downcast is just plain old static_cast

*/

#include <iostream>
#include <boost/cast.hpp>
using namespace std;

struct base {
	virtual ~base() { }
};

struct derived1 : public base {
	void foo() {
		cout << "derived1::foo() " << endl;
	}
};

struct derived2 : public base {
	void foo() {
		cout << "dervied2::foo() " << endl;
	}
};


//Uses static_cast
void older(base* p) {
	derived1* pD = static_cast<derived1*>(p);  //This will cause undefined behavior.
	pD->foo();
}

//uses polymorphic_downcast
void newer(base* p) {
	derived1* pD = boost::polymorphic_downcast<derived1*>(p); //This will cause an assertion debug builds.
	pD->foo();
}

int main() {
	derived2* pD = new derived2;
	older(pD);
	newer(pD);

	return 0;
}

/*
Use -D NDEBUG for release build.
See the difference in output in DEBUG n RELEASE builds
*/
