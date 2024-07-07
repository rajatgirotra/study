/*

Because the VPTR determines the virtual function behavior of the object, you can see how its critical that the VPTR always be pointing to the proper VTABLE. You don't ever want to be able to make a call to a virtual function before the VPTR is properly initialized. Of course, the place where initialization can be guaranteed is in the constructor, but none of the Instrument examples has a constructor.


Its important to realize that upcasting deals only with addresses. If the compiler has an object, it knows the exact type and therefore (in C++) will not use late binding for any function calls  or at least, the compiler doesnt need to use late binding. For efficiency sake, most compilers will perform early binding when they are making a call to a virtual function for an object because they know the exact type. Heres an example:

*/

//: C15:Early.cpp
// Early binding & virtual functions
#include <iostream>
#include <string>
using namespace std;

class Pet {
public:
  virtual string speak() const { return ""; }
  virtual ~Pet() {}
};

class Dog : public Pet {
public:
  string speak() const { return "Bark!"; }
};

int main() {
  Dog ralph;
  Pet* p1 = &ralph;
  Pet& p2 = ralph;
  Pet p3;
  // Late binding for both:
  cout << "p1->speak() = " << p1->speak() <<endl;
  cout << "p2.speak() = " << p2.speak() << endl;
  // Early binding (probably):
  cout << "p3.speak() = " << p3.speak() << endl;
} ///:~

/*

In p1->speak( ) and p2.speak(), addresses are used, which means the information is incomplete: p1 and p2 can represent the address of a Pet or something derived from Pet, so the virtual mechanism must be used. When calling p3.speak() theres no ambiguity. The compiler knows the exact type and that its an object, so it cant possibly be an object derived from Pet  its exactly a Pet. Thus, early binding is probably used. However, if the compiler doesnt want to work so hard, it can still use late binding and the same behavior will occur.

*/
