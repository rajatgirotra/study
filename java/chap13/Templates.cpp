/*
Please read LostInformation.java first
The C++ approach
Here’s a C++ example which uses templates. You’ll notice that the syntax for parameterized types is quite similar,
because Java took inspiration from C++:
 */
#include <iostream>
using namespace std;
template<class T>
class Manipulator
{
	T obj;
public:
	Manipulator(T x) { obj = x; }
	void manipulate() { obj.f(); }
};

class HasF {
public:
	void f() { cout << "HasF::f()" << endl; }
};

int main()
{
	HasF hf;
	Manipulator<HasF> manipulator(hf);
	manipulator.manipulate();
}
/* Output:
HasF::f()

The Manipulator class stores an object of type T. What’s interesting is the manipulate( ) method, which calls a method f( ) on
obj. How can it know that the f( ) method exists for the type parameter T?
The C++ compiler checks when you instantiate the template, so at the point of instantiation of Manipulator <HasF>,
it sees that HasF has a method f( ).
If it were not the case, you’d get a compile-time error, and thus type safety is preserved.

Writing this kind of code in C++ is straightforward because when a template is instantiated, the template code knows the type
of its template parameters.

Please read HasF.java next
*/
