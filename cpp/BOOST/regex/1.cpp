/* Please read Must_Read_1.tx first
*/

#include <boost/regex.hpp>
#include <iostream>
using namespace std;

int main() {
   boost::regex reg("(A.*)"); //Match A followed by zero or more occurences or any character.

   bool b = boost::regex_match("This expression could match from A and beyond.", reg);
   cout << boolalpha << b << endl;

   bool b1 = boost::regex_match("As this string starts with A, does it match??.", reg);
   cout << boolalpha << b1 << endl;

   return 0;
}

/*
Please read 2.cpp next
*/
