/*
One use of intrusive_ptr is when you want to pass the this pointer to function that takes a smart pointer. If you use shared_ptr in this case, you'll get double deletion and a program crash as you get in 14_*.cpp.
In such a case, you can use intrusive_ptr.
*/

#include <iostream>
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
using namespace std;

class A;

void do_something(boost::intrusive_ptr<A> p);

class reference_counter {
private:
	int ref_count;

public:
	reference_counter() : ref_count(0) { }

	friend void intrusive_ptr_add_ref(reference_counter* poT) {
		poT->add_ref();
	}

	void add_ref() {
		++ref_count;
	}

	friend void intrusive_ptr_release(reference_counter* poT) {
		if(poT->release() <= 0)
			delete poT;
	}

	int release() {
		return --ref_count;
	}
	int getCount() { return ref_count; }
};

class A : public reference_counter {
public:
	void do_stuff() {
		do_something(this); //-> this gets converted to intrusive_ptr due to the converting c'tor.
		cout << getCount() << endl;
	}
};

int main() {
	boost::intrusive_ptr<A> p(new A());
	cout << p->getCount() << endl;
	p->do_stuff();
	return 0;
}

void do_something(boost::intrusive_ptr<A> p)
{
   cout << p->getCount() << endl;
   cout << &p << endl;
}
