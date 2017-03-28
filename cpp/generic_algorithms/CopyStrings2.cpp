//The following program illustrates yet another variation of the copy algorithm:

//: C06:CopyStrings2.cpp
// Replaces strings that satisfy a predicate.
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;
 
// The predicate
bool contains_e(const string& s) {
  return s.find('e') != string::npos;
}
 
int main() {
  string a[] = {"read", "my", "lips"};
  const size_t SIZE = sizeof a / sizeof a[0];
  string b[SIZE];
  string* endb = replace_copy_if(a, a + SIZE, b,
    contains_e, string("kiss"));
  string* beginb = b;
  while(beginb != endb)
    cout << *beginb++ << endl;
} ///:~

/* 
Instead of just ignoring elements that dont satisfy the predicate, replace_copy_if( ) substitutes a fixed value for such elements when populating the output sequence. The output is:

kiss
my
lips
 
because the original occurrence of read, the only input string containing the letter e, is replaced by the word kiss, as specified in the last argument in the call to replace_copy_if( ).

*/
