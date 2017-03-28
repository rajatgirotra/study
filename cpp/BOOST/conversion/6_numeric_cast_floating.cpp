/*
numeric_cast does not help with loss of precision when converting between floating point types (float, double, long double). The reason is that the conversions between float, double, and long double aren't susceptible to the implicit conversions of integer types (i.e the integer value does not get modified, only there is loss of decimal points).

*/

#include <iostream>
#include <boost/cast.hpp>

double d = 0.123456789123456;
float  f = 0.123456;

int main() {
try {
  f = boost::numeric_cast<float>(d);
	std::cout << f << std::endl;
}
catch(boost::bad_numeric_cast& e) {
    std::cout << e.what();
}
}
