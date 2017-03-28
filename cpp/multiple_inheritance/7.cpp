/*

If a class has multiple direct base classes that share member functions of the same name, and you call one of those member functions, the compiler doesnt know which one to choose. The following sample program would report such an error:

*/
//: C09:AmbiguousName.cpp {-xo}
#include <iostream>
#include <string>
using namespace std;
 
class Top {
public:
  virtual ~Top() {}
};
 
class Left : virtual public Top {
public:
  void f() {}
};
 
class Right : virtual public Top {
public:
  int f(string s) {}
};
 
class Bottom : public Left, public Right {};
 
int main() {
  Bottom b;
  b.f(); // Error here
} ///:~
 
/*

The class Bottom has inherited two functions of the same name (the signature is irrelevant, since name lookup occurs before overload resolution), and there is no way to choose between them. The usual technique to disambiguate the call is to qualify the function call with the base class name:

What is meant by name lookup occurs before overload resolution is that the compiler first needs to decide which class has the function f(), then close in on one class. After that it decides whether there are any overloaded functions available there; and if yes; which one to choose amongst them.

So here it is unable to decide as the function f() exists in both Left and Right base classes leading to ambiguity.


*/
