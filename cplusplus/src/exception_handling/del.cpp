#include <iostream>
#include <string>
#include <exception>
#include <memory>

using namespace std;

class Foo {
private:
	void* ptr;

public:
	Foo() {
		ptr = new char[20];
		cout << "Foo::Foo()" << endl;	
	};

	~Foo() {
		cout << "Foo::~Foo()" << endl;
		delete[] ptr;
	}
};

int main() {
	auto_ptr<Foo> apFoo(new Foo());

}


