#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <iostream>
using namespace std;

struct Shoe {
	~Shoe() {
		cout << "Buckle my shoe" << endl;
	}
};

int add_one(const boost::scoped_ptr<int>& ptr) {
	return ++*ptr;
}

class MyClass {
static int i;
public:
	int id;
	MyClass() : id(i++)
        { }

	~MyClass() {
		cout << "MyClass d'tor  destroying id: " << id << endl;
	}

	void display() {
		cout << "I am MyClass with id: " << id << endl;
	}
};

int MyClass::i = 0;

int main() {
	Shoe s;

	boost::scoped_ptr<int> scopedPtr(new int());

	cout << add_one(scopedPtr) << "  ";
	cout << add_one(scopedPtr) << "  ";

	if(scopedPtr) {
		cout << "scopedPtr is not NULL" << endl;
	} else {
		cout << "scopedPtr is NULL" << endl;
	}

	scopedPtr.reset();

	if(scopedPtr) {
		cout << "scopedPtr is not NULL" << endl;
	} else {
		cout << "scopedPtr is NULL" << endl;
	}

	boost::scoped_array<MyClass> arr(new MyClass[5]);

	arr[2].display();

	return 0;
}

