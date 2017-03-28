/*

Class templates work well with RTTI, since all they do is generate classes. As usual, RTTI provides a convenient way to obtain the name of the class youre in. The following example prints the order of constructor and destructor calls:

*/


//: C08:ConstructorOrder.cpp
// Order of constructor calls.
#include <iostream>
#include <typeinfo>
using namespace std;
 
template<int id> class Announce {
public:
  Announce() {
    cout << typeid(*this).name() << " constructor" << endl;
  }
  ~Announce() {
    cout << typeid(*this).name() << " destructor" << endl;
  }
};
 
class X : public Announce<0> {
  Announce<1> m1;
  Announce<2> m2;
public:
  X() { cout << "X::X()" << endl; }
  ~X() { cout << "X::~X()" << endl; }
};
 
int main() { X x; } ///:~


/*
 

This template uses a constant int to differentiate one class from another, but type arguments would work as well. Inside both the constructor and destructor, RTTI information produces the name of the class to print. The class X uses both inheritance and composition to create a class that has an interesting order of constructor and destructor calls. The output is
Announce<0> constructor
Announce<1> constructor
Announce<2> constructor
X::X()
X::~X()
Announce<2> destructor
Announce<1> destructor
Announce<0> destructor
 

Of course, you may get different output depending on how your compiler represents its name( ) information.

*/
