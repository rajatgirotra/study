#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace std;

class A;

void foo(boost::shared_ptr<A> spA);

class A : public boost::enable_shared_from_this<A> {
public:

	void foo() {
		//boost::shared_ptr<A> spA(this);
		::foo(shared_from_this());
	}

	void bar() {
		cout << "Hello World" << endl;
	}
};

void foo(boost::shared_ptr<A> spA) {
	spA->bar();
}


int main() {
	boost::shared_ptr<A> spA(new A());
	spA->foo();


	return 0;
}
