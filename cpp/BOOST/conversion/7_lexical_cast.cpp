/*
Lexical cast is used to convert one type into an another, hence it looks like a type converting cast. It is nothing but a conversion function, but conceptually it can be thought of as a cast. For lexical cast to work

1] Source type should be OutputStreamable. ie. the source should define a operator << () function.
2] Destination type should be InputStreamable. ie. the destination type should definr an operator >>().
3] Both types shoud be CopyConstructible.
4] The destination type should be DefaultContructible and Assignable.

Think of lexical_cast as using a std::stringstream as an interpreter between the string and other representation of a value.

*/

#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;

int main() {

	//string to int
	string s = "42";
	int i = boost::lexical_cast<int>(s);
	cout << "i: " << i << endl;

	//float to string
	float f = 456.34;
	s = boost::lexical_cast<string>(f);
	cout << "s: " << s << endl;

	//literal to double
	double d = boost::lexical_cast<double>("23.098");
	cout << "d: " << d << endl;

	//Failed conversion
	try {
		s = "-987Not an int";
		i = boost::lexical_cast<int>(s);
	}
	catch(boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
	}
	return 0;
}
