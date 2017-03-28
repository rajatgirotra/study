/*
The replace_if( ) algorithm changes the original sequence in place, instead of writing to a separate output sequence, as the following program shows:
*/

//: C06:ReplaceStrings.cpp
// Replaces strings in-place.
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;
 
bool contains_e(const string& s) {
  return s.find('e') != string::npos;
}
 
int main() {
  string a[] = {"read", "my", "lips"};
  const size_t SIZE = sizeof a / sizeof a[0];
  replace_if(a, a + SIZE, contains_e, string("kiss"));
  string* p = a;
  while(p != a + SIZE)
    cout << *p++ << endl;
} ///:~

