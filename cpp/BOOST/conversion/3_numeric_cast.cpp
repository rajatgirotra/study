/*
Conversions between integral types can often produce unexpected results. For example, a long can typically hold a much greater range of values than a short, so what happens when assigning a long to a short and the long's value is outside of short's range? The answer is that the result is implementation defined.

Signed to unsigned conversions between same size integers are fine, so long as the signed value is positive, but what happens if the signed value is negative? It turns into a large unsigned value, which is indeed a problem if that was not the intention. numeric_cast helps ensure valid conversions by testing whether the range is preserved and by throwing an exception if it isn't.

numeric_cast is a function template that looks like a C++ cast operator and is parameterized on both the destination and source types. The source type can be implicitly deduced from the function argument.

eg:
char c=boost::numeric_cast<char>(12);
float f=boost::numeric_cast<float>(3.001);

*/

/*

Lets talk about signed integral types first. In C++, we have 4 signed integral types.

1] signed char
2] short int (short)
3] int
4] long int

The C++ standard says: When assigning one signed integral type to another, if the destination type is signed, the value is unchanged if it can be represented in the destination type; otherwise, the value is implementation-defined.
 eg:
*/

#include <iostream>
#include <boost/cast.hpp>
#include <boost/limits.hpp>
using namespace std;

int main() {
	cout << "larger to smaller example" << endl;

	long l = std::numeric_limits<short>::max();

	short s = l;

	cout << "s is: " << s << endl;

	//increment l and assign to s. This will cause implementation defined behavior. 
	s = ++l;
	cout << "s is: " << s << endl;

	//now using numeric_cast
	try {
		l = std::numeric_limits<short>::max();
		s = boost::numeric_cast<short>(l);
		cout << "s after numeric_cast is: " << s << endl;

		s = boost::numeric_cast<short>(++l);
		cout << "s after incrementing numeric_cast is: " << s << endl;
	} catch(boost::bad_numeric_cast& e) {
		cout << e.what() << endl;
	}
	return 0;
}
