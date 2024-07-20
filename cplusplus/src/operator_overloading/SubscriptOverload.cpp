#include <iostream>
using namespace std;

// subscript operators are always overloaded in pairs
class A {
public:
	static const unsigned int SIZE = 20;
	
private:
	int array[SIZE];

public:

	int& operator[] (const int& index) {
		return array[index];
	}

	const int& operator[] (const int& index) const {
		return array[index];
	}
};

int main() {
	A a;

	int i;
	for(i = 0; i <  A::SIZE; ++i ) {
		a[i] = i * 5;
	}

	
	for(i = 0; i <  A::SIZE; ++i ) {
		cout << a[i] << endl;
	}

	return 0;
}
