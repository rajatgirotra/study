/*
You already know about asserts. C++ asserts work at run-time and if it fails, an error is displayed and the program aborts.
Boost on the other hand provides a macro which can assert at compile time.. Yes really..!! its called BOOST_STATIC_ASSERT.
This can be used at different scopes. We'll first see an example usage at class scope, followed by usage at function scope.

Class Scope: Lets say we create a template class where we want the template parameter to be only of integral type. To know the type of the parameter, we use another
boost library called Boost.type_traits; which provides a predicate called boost::is_integral. This predicate performs a compile time evaluation of its argument and tells if it is an integer or not.
*/

#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
using namespace std;

template <typename T>
class only_compatible_with_integral_types {
	BOOST_STATIC_ASSERT(boost::is_integral<T>::value);
};

int main() {
	only_compatible_with_integral_types<float> d; //--> This will cause compile time assertion/error.
	return 0;
}

