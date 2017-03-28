/*

RTTI only works for complete types, meaning that all class information must be available when typeid is used. In particular, it doesnt work with void pointers:

*/


//: C08:VoidRTTI.cpp
// RTTI & void pointers.
#include <iostream>
#include <typeinfo>
using namespace std;
 
class Stimpy {
public:
  virtual void happy() {}
  virtual void joy() {}
  virtual ~Stimpy() {}
};
 
int main() {
  void* v = new Stimpy;
  // Error:
//!  Stimpy* s = dynamic_cast<Stimpy*>(v);
  // Error:
//!  cout << typeid(*v).name() << endl;
} ///:~
 
/*
A void* truly means no type information.[119]

*/
