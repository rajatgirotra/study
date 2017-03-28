/*
Understanding boost::bind
Before you go through boost::bind. Its good if you understand std::unary_function, std::binary_function, std::binder1st, std::binder2nd, std::bind1st, std::bind2nd.
You can read about these on google. Also remember these are deprecated from C++0x11, so you should start using boost::bind or std::bind more often now.

boost::bind() is just a generalisation of the concept of std::bind1st and std::bind2nd. But it is more generic. Basically, it works with

1] Functions
2] Function Pointers
3] Function Objects
4] Member Functions Pointers.

It is just a template function.
Basically, you just encapsulates a function and its arguments and you get back a function object. Just call that function object and the encapsulated function is called.
Lets see it in action.

Remember:
1] It is an overloaded template function.
2] It returns you a function object.
*/

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
using namespace std;

int f(const int& x, const int& y) {
	return x + y;
}

int g(int x, int y, int z) {
	return x + y + z;
}

int (*poF)(const int&, const int&) = 0;

class Counter {
private:
	static int objectCount;
	int objectNumber;
public:
	Counter() : objectNumber(++objectCount) {
		//cout << "Counter c'tor" << endl;
	}

	Counter(const Counter&) : objectNumber(++objectCount) {
		//cout << "Counter copy c'tor" << endl;
	}

	~Counter() {
		//cout << "Counter d'tor" << endl;
		--objectCount;
	}

	int getObjectCount() const {
		return objectCount;
	}
};

int Counter::objectCount = 0;

void foo (const Counter& counter) {
	cout << "Counter object count: " << counter.getObjectCount() << endl;
}


struct F {
	int operator() (const int& a, const int& b) { return a - b; }
	bool operator() (const long& a, const long& b) { return a == b; }
};

struct IsOdd : public unary_function <int, bool> {
	bool operator() (const int& x) {
		if (x % 2 == 0)
			return false;
		else
			return true;
	}
};

struct X {
	bool foo(int a) {cout << "X::foo: " << a << endl; return true; }
};

int main() {
	/*
	Using boost::bind() with functions and function pointers
	*/
	//3
	cout << boost::bind(f, 1, 2)() << endl;	 //the function object returned is called using the function call operator.
	//Remember, here boost::bind returns you a nullary function object (i.e a function object with no arguments).
	//The arguments 1 and 2 are encapsulated inside the function object.
	//Remember the function object returns the same type as f(1, 2)

	//6
	cout << boost::bind(g, 1, 2, 3)() << endl;

	//13
	poF = &f;
	cout << boost::bind(poF, 4, 9)() << endl;

	//33
	//You also have the flexibility of binding only a few of the arguments.
	cout << boost::bind(f, _1, 10)(23) << endl;  // _1 is a placeholder whose value is given separately in the argument list.
	//This gives you a function object with one parameter (23).

	//12
	cout << boost::bind(g, _3, _3, _3)(2, 3, 4) << endl;

	//boost::bind takes it arguments by value. Use boost::ref() if you need to pass the argument by reference.
	Counter c;
	boost::bind(foo, boost::ref(c))();
	//boost::bind(foo, c)();



	
	/* Using boost::bind with function objects */
	//With functin objects, you must specify to boost::bind() the return type of your function object. For
	//Eg: here we have two: either int or bool.
	F f;
	cout << boost::bind<int> (f, 5, 5)() << endl;
	cout << std::boolalpha << boost::bind<bool> (f, 2L, 2L)() << endl;

	//However, if your function object has a nested result_type defined, then the return type parameter may be ignored.
	IsOdd isOdd;
	cout << std::boolalpha << boost::bind(boost::ref(isOdd), 4)() << endl;
	//As before a copy of the function object is created. So use boost::ref() or boost::cref(). This becomes mandatory if the object is not copyable anyway, or is expensive to copy.




	//Using boost::bind with pointers to members.
	/*
	boost provided a function mem_fn() which basically accepts a pointer to member function and returns a function object that accepts a 
	1) pointer, 
	2) reference, or
	3) a smart pointer as its first argument (This is basically a reference to this), followed by the arguments of the member function.

	boost::bind(&X::f, args) is equivalent to boost::bind<R> (boost::mem_fn(&X::f), args)
	*/
	X x;
	boost::shared_ptr<X> XPtr (new X());
	boost::bind(&X::foo, &x, 4)(); //Pointer.
	boost::bind(&X::foo, boost::ref(x), 10)(); //Reference
	boost::bind(&X::foo, x, 20)();
	boost::bind(&X::foo, XPtr, 30);
	
	boost::function2<bool, X*, int> onClick;
	onClick = boost::bind(&X::foo, boost::ref(XPtr), 25);

	onClick(&x, 30);

	return 0;
}
