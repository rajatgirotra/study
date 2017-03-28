/*
Unsigned integral types have a very interesting property. Any numeric value can be legally assigned to them! There is no notion of positive or negative overflow when it comes to unsigned types. They are reduced modulo the number that is one greater than the largest value of the destination type. This is called value wrapping. Value wrapping is not an error according to the standard. So if you think your program should treat value wrapping as an error, use numeric_cast, otherwise not.

*/

#include <iostream>
#include <boost/limits.hpp>
#include <boost/cast.hpp>
using namespace std;

int main() {
	unsigned char c ;
	long l = std::numeric_limits<unsigned char>::max() + 14;
	cout <<"l = " << l << endl;
	
	//c = boost::numeric_cast<unsigned char>(l);
	c = l;
	//c = -789;
	cout <<"c = " << (int)c << endl;

	long reduced = l % (std::numeric_limits<unsigned char>::max() + 1);
	cout << "reduced is =  " << reduced << endl;

	return 0;
}
