/*
you can also create the intrusive_ptr_release and intrusive_ptr_add_ref functions as friends of the reference_counter class. This will allow them to be found easily using ASL, even if the derived class of reference_counter is defined in a separate namespace.
*/

#include <iostream>
#include <boost/intrusive_ptr.hpp>
using namespace std;



/* A very important point to note is that these functions should be defined in the same namespace as the class which they are managing.
It is because these functions are called without any qualification, so the compiler will be able to locate them only via argument dependent lookup.

We now define a reference_counter class
*/

class reference_counter {
private:
	int ref_count;

public:

	reference_counter() : ref_count(0) { }

	virtual ~reference_counter() { }

	friend void intrusive_ptr_add_ref(reference_counter* poT) {
		poT->add_ref();
		cout << "intrusive_ptr_add_ref() called: "<<poT->getCount() << endl;
	}

	friend void intrusive_ptr_release(reference_counter* poT) {
		if(poT->release() <= 0)
			delete poT;
		cout << "intrusive_ptr_release() called: "<<poT->getCount() <<endl;
	}

	void add_ref() {
		++ref_count;
	}

	int release() {
		--ref_count;
		return ref_count;
	}

	int getCount() { return ref_count; }


protected:
	reference_counter operator = (const reference_counter&) {
		return *this;
	}

private:
	reference_counter(const reference_counter&);
};


/* Now we create a subclass from reference_counter and use it with intrusive_ptr */

class some_class : public reference_counter {
	public:
		some_class() {
			cout <<"Some class c'tor"<<endl;
		}

		~some_class() {
			cout <<"some class d'tor"<<endl;
		}

		some_class(const some_class& rhs) {
			cout << "some class copy c'tor "<<endl;
		}
};

int main() {
	boost::intrusive_ptr<some_class> p1(new some_class());
	boost::intrusive_ptr<some_class> p2(p1);
	return 0;
}

