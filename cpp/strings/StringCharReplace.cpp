//: C03:StringCharReplace.cpp
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
using namespace std;
 
int main() {
  string s("aaaXaaaXXaaXXXaXXXXaaa");
  cout<<"s before = "<<s<<endl;
  replace(s.begin(), s.end(), 'X', 'Y');
  assert(s == "aaaYaaaYYaaYYYaYYYYaaa");
  cout<<"s after = "<<s<<endl;
} ///:~

/*
 
Notice that this replace( ) is not called as a member function of string. Also, unlike the string::replace( ) functions that only perform one replacement, the replace( ) algorithm replaces all instances of one character with another.

The replace( ) algorithm only works with single objects (in this case, char objects) and will not replace quoted char arrays or string objects. Since a string behaves like an STL sequence, a number of other algorithms can be applied to it, which might solve other problems that are not directly addressed by the string member functions.

*/
