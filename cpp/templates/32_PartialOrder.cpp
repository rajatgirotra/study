/*

We mentioned earlier that an ordinary function overload of min( ) is preferable to using the template. If a function already exists to match a function call, why generate another? In the absence of ordinary functions, however, it is possible that overloaded function templates can lead to ambiguities. To minimize the chances of this, an ordering is defined for function templates, which chooses the most specialized template, if such exists. A function template is considered more specialized than another if every possible list of arguments that matches it also matches the other, but not the other way around. Consider the following function template declarations, taken from an example in the C++ Standard document:
template<class T> void f(T);
template<class T> void f(T*);
template<class T> void f(const T*);
 

The first template can be matched with any type. The second template is more specialized than the first because only pointer types match it. In other words, you can look upon the set of possible calls that match the second template as a subset of the first. A similar relationship exists between the second and third template declarations above: the third can only be called for pointers to const, but the second accommodates any pointer type. The following program illustrates these rules:

*/


//: C05:PartialOrder.cpp
// Reveals ordering of function templates.
#include <iostream>
using namespace std;
 
template<class T> void f(T) {
  cout << "T" << endl;
}
 
template<class T> void f(T*) {
  cout << "T*" << endl;
}

template<class T> void f(const T*) {
  cout << "const T*" << endl;
}
 
int main() {
  f(0);            // T
  int i = 0;
  f(&i);           // T*
  const int j = 0;
  f(&j);           // const T*
} ///:~

/*
 

The call f(&i) certainly matches the first template, but since the second is more specialized, it is called. The third cant be called here since the pointer is not a pointer to const. The call f(&j) matches all three templates (for example, T would be const int in the second template), but again, the third template is more specialized, so it is used instead.

If there is no most specialized template among a set of overloaded function templates, an ambiguity remains, and the compiler will report an error. That is why this feature is called a partial orderingit may not be able to resolve all possibilities. Similar rules exist for class templates.

*/

