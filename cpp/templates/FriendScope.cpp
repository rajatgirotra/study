/*
A friend function declaration inside a class allows a non-member function to access non-public members of that class. If the friend function name is qualified, it will be found in the namespace or class that qualifies it. If it is unqualified, however, the compiler must make an assumption about where the definition of the friend function will be, since all identifiers must have a unique scope. The expectation is that the function will be defined in the nearest enclosing namespace (non-class) scope that contains the class granting friendship. Often this is just the global scope. The following non-template example clarifies this issue:
*/

//: C05:FriendScope.cpp
#include <iostream>
using namespace std;
 
class Friendly {
  int i;
public:
  Friendly(int theInt) { i = theInt; }
  friend void f(const Friendly&); // Needs global def.
  void g() { f(*this); }
};
 
void h() {
  f(Friendly(1));  // Uses ADL
  f(1);  // Uses ADL
}
 
void f(const Friendly& fo) {  // Definition of friend
  cout << fo.i << endl;
}
 
int main() {
  h(); // Prints 1
  Friendly(2).g(); // Prints 2
} ///:~
 
/*
The declaration of f( ) inside the Friendly class is unqualified, so the compiler will expect to be able to eventually link that declaration to a definition at file scope (the namespace scope that contains Friendly in this case). That definition appears after the definition of the function h( ). The linking of the call to f( ) inside h( ) to the same function is a separate matter, however. This is resolved by ADL. Since the argument of f( ) inside h( ) is a Friendly object, the Friendly class is searched for a declaration of f( ), which succeeds. If the call were f(1) instead (which makes some sense since 1 can be implicitly converted to Friendly(1)), the call should fail, since there is no hint of where the compiler should look for the declaration of f( ). The EDG compiler correctly complains that f is undefined in that case.
*/
