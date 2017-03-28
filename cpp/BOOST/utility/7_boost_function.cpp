/*
Boost.Function - This is a simple set of template classes which wraps a function object or function pointer
A function object is an object of a class which overloads the function call "()" operator.

Very simple to use:
You simple create an object of class
   boost::functionN<typename ReturnType, typename Arg1, typename Arg2, ... , typename ArgN>
where N is the no. of arguments to your function.
When you create an object, it basically is empty. You assign it a function object or function pointer and then call
it in a trivial see as you see below.

I think in most implementations, N can go upto 10.
*/

#include <iostream>
#include <boost/function.hpp>
#include <string>
using namespace std;


class NoArg {
public:
	void operator() (){
		cout << "NoArg" << endl;
	}
};

class OneArg {
public:
	const char* operator () (double d) {
		cout << "OneArg: " << d << endl;
		return "Hello World";
	}
};

class TwoArg {
public:
	OneArg operator () (const std::string& str, const NoArg&) {
		cout << "Two Arg: " << str << endl;
		return OneArg();
	}
};

int foo() {
	cout << "Function foo with no arguments returning -89\n";
	return -89;
}

int (*fooFuncPtr)() = &foo;

int main() {
	boost::function0<void> fun0; // void is the return type, function is currently empty.
	NoArg noarg;
	fun0 = noarg; // Assign a function object.
	fun0(); // Call it

	boost::function1<const char*, double> fun1;
	OneArg oneArg;
	fun1 = oneArg;
	cout << fun1(123.345) << endl;

	boost::function2<OneArg, const std::string&, const NoArg&> fun2;
	TwoArg twoArg;
	fun2 = twoArg;
	fun2("Goodbye, Cruel World", noarg);
	
	//An exception is thrown if a boost::function is empty.
	boost::function0<int> fun0Empty;
	try {
		fun0Empty();
	} catch (const boost::bad_function_call& e) {
		cout << "Exception Caught: " << e.what() << endl;
	}

	//So either use a try catch block, or else check for empty().
	if(fun0Empty.empty()) {
		cout << "boost::function is empty, cannot make a function call" << endl;
	} else {
		fun0Empty();
	}

	// Attaching a function pointer to a boost::function.
	fun0Empty = &foo;
	fun0Empty();

	fun0Empty = fooFuncPtr;
	fun0Empty();
	return 0;
}
