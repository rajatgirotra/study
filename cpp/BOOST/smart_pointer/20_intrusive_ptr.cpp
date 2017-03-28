/*
Wrapping shared_ptr in intrusive ptr. Very important to understand. A very nice solution indeed.
*/

#include <iostream>
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
using namespace std;

class A;

void do_something(boost::intrusive_ptr<A> p);
void do_something(boost::shared_ptr<A> p);

class reference_counter {
private:
	int ref_count;

public:
	reference_counter() : ref_count(0) { }

	virtual ~reference_counter() { }

	friend void intrusive_ptr_add_ref(reference_counter* poT) {
		poT->add_ref();
	}

	void add_ref() {
		++ref_count;
	}

	friend void intrusive_ptr_release(reference_counter* poT);

	int release() {
		return --ref_count;
	}
	int getCount() { return ref_count; }
};

void intrusive_ptr_release(reference_counter* poT) {
	cout << "refCount going down from: " << poT->getCount() << endl;
	if(poT->release() <= 0)
		delete poT;
}

class A : public reference_counter {
public:
	void do_stuff() {
		intrusive_ptr_add_ref(this);
		cout << "In do_stuff member function after calling intrusive_ptr_add_ref manually. " << getCount() <<endl;
		boost::shared_ptr<A> p(this, &intrusive_ptr_release);
		cout <<"After creating a shared_ptr in do_stuff. Refcount of shared_ptr: " << p.use_count() << endl;
		cout <<"Calling do_something " << endl;
		do_something(p);
		cout << "In do_stuff member function after calling do_something. UseCount: " << p.use_count() <<endl;
		cout << "In do_stuff member function after calling do_something. refCount: " << getCount() <<endl;
	}

	~A() {
		cout << "Class A d'tor running" << endl;
	}
};

int main() {
	boost::intrusive_ptr<A> p(new A());
	cout << "Ref count of intrusive ptr after creating it. Should be 1: " << p->getCount() << endl;
	cout << "Calling do_stuff member function" << endl;
	p->do_stuff();
        cout << p->getCount() << endl;
	return 0;
}

void do_something(boost::intrusive_ptr<A> p)
{
   cout << p->getCount() << endl;
   cout << &p << endl;
}

void do_something(boost::shared_ptr<A> p) {
	cout << "In do something ordinary function: useCount of shared_ptr. Should be 2: " << p.use_count() << endl;
	cout << "Hello World" << endl;
}
