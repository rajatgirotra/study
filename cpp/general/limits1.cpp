// util/limits1.cpp
#include <iostream>
#include <limits>
#include <string>
using namespace std;
int main()
{
//use textual representation for bool
cout << boolalpha;
//print maximum of integral types
cout << "max(short): " << numeric_limits<short>::max() << endl;
cout << "max(int): " << numeric_limits<int>::max() << endl;
cout << "max(unsigned int): " << numeric_limits<unsigned int>::max() << endl;
cout << "max(long): " << numeric_limits<long>::max() << endl;
cout << endl;
//print maximum of floating-point types
cout << "max(float): "
<< numeric_limits<float>::max() << endl;
cout << "max(double): "
<< numeric_limits<double>::max() << endl;

cout << "max(long double): "
<< numeric_limits<long double>::max() << endl;
cout << endl;
//print whether char is signed
cout << "is_signed(char): "
<< numeric_limits<char>::is_signed << endl;
cout << endl;
//print whether numeric limits for type string exist
cout << "is_specialized(string): "
<< numeric_limits<string>::is_specialized << endl;
cout << "is_specialized(char): "
<< numeric_limits<char>::is_specialized << endl;
}
