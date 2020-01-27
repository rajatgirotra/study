/*

You can easily put static data members in classes that are nested inside other classes. The definition of such members is an intuitive and obvious extension  you simply use another level of scope resolution. However, you cannot have static data members inside local classes (a local class is a class defined inside a function). Thus,

*/

//: C10:Local.cpp
// Static members & local classes
#include <iostream>
using namespace std;

// Nested class CAN have static data members:
class Outer {
  class Inner {
    static int i; // OK
  };
};

int Outer::Inner::i = 47;

// Local class cannot have static data members:
void f() {
  class Local {
  public:
    Local() { cout<<"Local c'tor"<<endl; }
    ~Local() { cout<<"Local d'tor"<<endl; }
//! static const int i;  // Error
    // (How would you define i?)
  } x;
} 

int main() { Outer x; f(); } ///:~

