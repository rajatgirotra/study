/*
Here we demonstrate a simple function written with the help of lexical cast; which is very simple and reusable for different types.
It shows how to convert from any data type to std::string.
*/

#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;

template <typename T>
std::string toString(const T& rhs) {
	try {
		return boost::lexical_cast<std::string>(rhs);
	}
	catch(boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
		return "";
	}
}

int main() {
	string s = toString(412);
	cout << s << endl;

	s = toString(123.456);
	cout << s << endl;

	return 0;
}
