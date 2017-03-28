/*

Theres something that happens during destruction that you might not immediately expect. If youre inside an ordinary member function and you call a virtual function, that function is called using the late-binding mechanism. This is not true with destructors, virtual or not. Inside a destructor, only the local version of the member function is called; the virtual mechanism is ignored.

*/

//: C15:VirtualsInDestructors.cpp
// Virtual calls inside destructors
#include <iostream>
using namespace std;

class Base {
public:
  virtual ~Base() { 
    cout << "~Base()\n"; 
    f(); 
  }
  virtual void f() { cout << "Base::f()\n"; }
};

class Derived : public Base {
public:
  ~Derived() { cout << "~Derived()\n"; f(); }
  void f() { cout << "Derived::f()\n"; }
};

int main() {
  Base* bp = new Derived; // Upcast
  delete bp;
} ///:~

/*

During the destructor call, Derived::f( ) is not called, even though f( ) is virtual.


Why is this? Suppose the virtual mechanism were used inside the destructor. Then it would be possible for the virtual call to resolve to a function that was farther out (more derived) on the inheritance hierarchy than the current destructor. But destructors are called from the outside in (from the most-derived destructor down to the base destructor), so the actual function called would rely on portions of an object that have already been destroyed! Instead, the compiler resolves the calls at compile-time and calls only the local version of the function. Notice that the same is true for the constructor (as described earlier), but in the constructors case the type information wasnt available, whereas in the destructor the information (that is, the VPTR) is there, but is isnt reliable.

*/

