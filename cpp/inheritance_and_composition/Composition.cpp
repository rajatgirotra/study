//: C14:Composition.cpp
// Reuse code with composition
#include "Useful.h"

class Y {
  int i;
public:
  X x; // Embedded object
  Y() 
  {
     cout<<"Y::Y() called"<<endl;
     i = 0;
  }
  void f(int ii) { i = ii; }
  int g() const { return i; }
};

int main() {
  Y y;
  y.f(47);
  y.x.set(37); // Access the embedded object
  cout<<"Y.i = "<<y.g()<<endl;
  cout<<"Y.X.i = "<<y.x.read()<<endl;
  return 0;
} ///:~

