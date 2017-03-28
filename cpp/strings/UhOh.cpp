/*
C++ strings may not be initialized with single characters or with ASCII or other integer values. You can initialize a string with a number of copies of a single character, however:
*/

//: C03:UhOh.cpp
#include <string>
#include <cassert>
#include <iostream>
using namespace std;
 
int main() {
  // Error: no single char inits
  //! string nothingDoing1('a');
  // Error: no integer inits
  //! string nothingDoing2(0x37);
  // The following is legal:
  string okay(15, '*');
  //assert(okay == string("aaaaa"));
   cout<<okay<<endl;
} ///:~

