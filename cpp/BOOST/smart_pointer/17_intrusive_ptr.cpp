/*
An intrusive_ptr is just like a shared_ptr, but the developer needs to provide a reference_count of its own.
When an intrusive_ptr has to increment or decrement a reference_count, it does so by calling two functions without any qualification.

For increment: intrusive_ptr_add_ref
For decrement: intrusive_ptr_release

Also, intrusive_ptr_release has the responsibility to delete the pointer when the count drops to zero.

The most common usage of the intrusive_ptr is to definte the two functions above as template functions, and then forward
the calls to member functions the class which you are managing. The functions take as argument, a pointer to the type you are holding and
do not return anything.

*/

#include <iostream>
#include <boost/intrusive_ptr.hpp>
using namespace std;

template <typename T>
void intrusive_ptr_add_ref(T* poT) {
	poT->add_ref();
	cout << "intrusive_ptr_add_ref() called: "<<poT->getCount() << endl;
}

template <typename T>
void intrusive_ptr_release(T* poT) {
	if(poT->release() <= 0)
		delete poT;
	cout << "intrusive_ptr_release() called: "<<poT->getCount() <<endl;
}

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

/*
the implementation of reference_counter is not thread-safe, and therefore cannot be used in multithreaded applications without adding synchronization.
*/
