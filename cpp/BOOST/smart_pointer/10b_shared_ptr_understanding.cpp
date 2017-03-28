#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;

void foo(const boost::shared_ptr<int> spInt) {
//void foo(const boost::shared_ptr<int>& spInt) {
	cout << "In foo()"<< endl;
	cout << "sp.use_count() " << spInt.use_count() << endl;
	cout << "sp.unique() " << spInt.unique() << endl;
	cout << *spInt << endl;
}

int main() {
	boost::shared_ptr<int> spInt(new int(-976));
	cout << "In main()"<< endl;
	cout << "sp.use_count() " << spInt.use_count() << endl;
	cout << "sp.unique() " << spInt.unique() << endl;
	cout << *spInt << endl;
	cout << endl;

	foo(spInt);

	return 0;
}

/*
So when you pass shared_ptr's by reference, reference count is not updated
otes: use_count() is not necessarily efficient. Use only for debugging and testing purposes, not for production code.
*/

