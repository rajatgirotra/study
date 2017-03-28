/*

If you want the size of the string to remain unchanged, use the replace( ) function to overwrite characters. There are a number of overloaded versions of replace( ), but the simplest one takes three arguments: an integer indicating where to start in the string, an integer indicating how many characters to eliminate from the original string, and the replacement string (which can be a different number of characters than the eliminated quantity). Here.s a simple example:

*/

//: C03:StringReplace.cpp
// Simple find-and-replace in strings.
#include <cassert>
#include <string>
#include <iostream>
using namespace std;
 
int main() {
  string s("A piece of text");
  cout<<s.size()<<endl;
  string tag("$tag$");
  s.insert(8, tag + ' ');
  cout<<s.size()<<endl;
  assert(s == "A piece $tag$ of text");
  int start = s.find(tag);
  assert(start == 8);
  assert(tag.size() == 5);
  s.replace(start, tag.size(), "hello there");
  cout<<s.size()<<endl;
  assert(s == "A piece hello there of text");
} ///:~

