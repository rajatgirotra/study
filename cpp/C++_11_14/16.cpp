#include <iostream>
#include <string>
using namespace std;

struct Base {
	public:
                static int iCounter;
                int tag;
		Base() : tag (++iCounter) {
			cout << "Base c'tor for tag: " << tag << endl;
		}

		~Base() {
			cout << "Base d'tor for tag: " << tag << endl;
		}


		Base(const Base& rhs) : tag (++iCounter) {
			cout << "Base classic copy c'tor for tag: " << tag << "   using tag: " << rhs.tag << endl;
		}

		Base(Base&& rhs) : tag (++iCounter)  {
			cout << "Base move copy c'tor for tag: " << tag << "   using tag: " << rhs.tag << endl;
                        //Exchange tag numbers to simulate movement
                        int tmp = tag; tag = rhs.tag; rhs.tag = tmp;
                        
		}

		Base& operator = (const Base& rhs) {
			cout << "Base classic assignment operator for tag: " << tag << "   using tag: " << rhs.tag<< endl;
			return *this;
		}

		Base& operator = (Base&& rhs) {
			cout << "Base move assignment operator for tag: " << tag << "   using tag: " << rhs.tag<< endl;
                        //Exchange tag numbers to simulate movement
                        int tmp = tag; tag = rhs.tag; rhs.tag = tmp;
			return *this;
		}

};

int Base::iCounter = 0;


struct Derv : public Base {
	public:
		Derv() {
			cout << "Derv c'tor" << endl;
		}

		~Derv() {
			cout << "Derv d'tor" << endl;
		}


		Derv(const Derv& rhs) : Base(rhs) {
			cout << "Derv classic copy c'tor" << endl;
		}

		Derv (Derv&& rhs) : Base(std::move(rhs)) {
			cout << "Derv move copy c'tor" << endl;
		}

		Derv& operator = (const Derv& rhs) {
			Base::operator=(rhs);
			cout << "Derv classic assignment operator" << endl;
			return *this;
		}

		Derv& operator = (Derv&& rhs) {
			Base::operator=(std::move(rhs));
			cout << "Derv move assignment operator" << endl;
			return *this;
		}
};
#if 0
Derv foo() {
    return Derv();
}
#endif

#if 0
Derv&& foo()
{
    static Derv d;
    return std::move(d);
}
#endif

Derv foo()
{
    static Derv d;
    return d;
}

int main() {
        cout << "Copy Construction first" << endl;
        Derv d1 = std::move(foo());  // --------->>> A
        cout << "Assignment operation next" << endl;
        d1 = foo(); 
	return 0;
}


/*
 * Ok Here's the all important learning.
 *
 * 1) See how you use std::move() in copy c'tor and assignment operator with move semantics to force the move versions of the same functions
 *    to be called in the base classes. This is because the rvalue references in copy c'tor and assignment operator will always a name, so the
 *    compiler will treat them as lvalues.
 *
 * 2) In function foo(), you return a Derv object by value. So in this case the compiler is clever to use NVRO.
 *    If compiler would not have used NVRO, then because foo() returns a temporary unnamed object, move copy c'tor would have been used.
 *    The other way that you can force move semantics is by changing the return type of foo() from Derv to Derv&&, so it becomes an
 *    unnamed rvalue reference. But in this case since it is a reference to a local variable which will be destroyed when foo() returns, 
 *    we cannot/should not use it in the copy c'tor as it is not reliable. 
 *    The solution is if I make the following change (ie make the return value as static in foo()).
 *
 *    Derv&& foo()
 *    {
 *        static Derv d;
 *        return d;
 *    }
 *
 *    If you return a const Derv& instead, then you will be retunring a reference to a local variable which is a sure recipe for disaster.
 *    As the local object will be destroyed as you leave the function.
 *
 * 3) If you instead return an rvalue reference, Derv&&, again same thing. Since an rvalue reference is also a reference, same as point 2.
 *    The local object will be destoyed anyway when foo() finishes.
 *
 *    So the question really is, how to force the compiler to use move semantics in line A. Simple, you have seen this before.
 *    Use std::move
 *    Derv d1 = std::move(foo()); // to force move semantics.
 *
 *  For assignment, move semantics is used as expected (as foo() returns an unnamed temporary object).
 */
