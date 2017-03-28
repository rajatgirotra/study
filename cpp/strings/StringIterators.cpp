//: C03:StringIterators.cpp
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
 
int main() {
  string source("Rajat Girotra");
  string s(source.begin() + 4, source.end() - 4);
  string s1(6, '*'); // --> Create a string repeating character * 6 times
  //assert(s == source);
  cout<<s<<endl;
  cout<<s1<<endl;
  return 0;
} ///:~

/*

The iterators are not restricted to begin( ) and end( ); you can increment, decrement, and add integer offsets to them, allowing you to extract a subset of characters from the source string.

*/
