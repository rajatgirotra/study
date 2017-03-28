/*
When deleting an object through a pointer, the result depends on whether the type being deleted is known at that time. Normally, the compiler does not complain about deleting an incomplete type (g++ compiler throws a warning), but if you do so , it is undefined behavior, as the d'tor may not be invoked.

checked_delete is in effect a static assertion that the class type is known upon deletion, enforcing the constraint that the d'tor will be called.

checked_delete is nothing but a template function in the boost:: namespace, the argument to this function is the pointer to be deleted. To use it, simply replace your delete(ptr) statements with checked_delete(ptr);

Think of checked_delete defined as follows:

template <typename T>
inline void checked_delete(T* x) {
	typedef char type_must_be_complete[sizeof(T)];
	delete x;
}

if the type is incomplete, sizeof() operator returns 0. Since it is illegal to create an array of size 0, the statement does not compile. This utility is very handy when writing templates that must ensure that they are instantiated only with complete types.
You could also use BOOST_STATIC_ASSERT(sizeof(T)) for this.

like checked_delete, you also have checked_array_delete for deleting array of pointers.

*/

#include <iostream>
#include <boost/checked_delete.hpp>
using namespace std;

class some_class;

some_class* create() {
	return 0;
}

int main() {
	some_class* ptr = create();
	//Uncomment the following line and see the warning reported by g++.
	//delete ptr; 

	boost::checked_delete(ptr);

	return 0;
}
