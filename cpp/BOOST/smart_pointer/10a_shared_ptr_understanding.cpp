/*
shared_ptr<T> can be implicitly converted to shared_ptr<U> whenever T* can be implicitly converted to U*. In particular, shared_ptr<T> is implicitly convertible to shared_ptr<T const>, to shared_ptr<U> where U is an accessible base of T, and to shared_ptr<void>.

i.e. is A is a base class and B is derived, then shared_ptr<B> is implicitly converted to shared_ptr<A>

*/

#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;

class A {
public:
	virtual void foo() const {
		cout << "A::foo()" << endl;
	}

	virtual ~A() {
		cout << "A::~A()" << endl;
	}
};

class B : public A {
public:
	void foo() const {
		cout << "B::foo()" << endl;
	}

	virtual ~B() {
		cout << "B::~B()" << endl;
	}
};


//void bar(boost::shared_ptr<void> ptr) {
//void bar(boost::shared_ptr<B const> ptr) {
//void bar(boost::shared_ptr<const B> ptr) {
void bar(boost::shared_ptr<A> ptr) {
	ptr->foo();
}


int main() {

	boost::shared_ptr<B> spB(new B());
	bar(spB); //converting shared_ptr<B> to shared_ptr<A> because B* is implicitly convertible to A*.

	return 0;
}

