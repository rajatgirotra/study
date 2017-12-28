/*
 * C++0x11 deprecates the use of NULL or 0 to assign a pointer a null value. Instead it introduces a nullptr keyword. So you should always use nullptr now.
 */

#include <iostream>
#include <typeinfo>
using namespace std;

#if 1
void foo(int) {
	cout << "foo(int) called" << endl;
}
#endif

void foo(char* s) {
	cout << "foo(char*) called "<< endl;
}


#if 1
void foo(std::nullptr_t x) {
	cout << "foo(std::nullptr_t) called" << endl;
}
#endif


int main() {
	//foo(0); //which one will be called. foo(int) or foo(char*).
	//foo(NULL); //which one will be called. foo(int) or foo(char*).
	//foo(nullptr); //which one will be called. foo(int) or foo(char*).

	//To eliminate the above ambiguities/confusion, use nullptr.
	
	char* s = nullptr;
	cout << typeid(decltype(nullptr)).name() << endl; //nullptr is actually a new type defined as std::nullptr_t
        //foo(s);

	std::nullptr_t a;
	//foo(nullptr);
	//foo(a);

        double* d = nullptr;
        foo(d);
        
	return 0;
}

/*
 * Here's the crux. With C++11, always initialize pointer types with nulltpr.
 */
