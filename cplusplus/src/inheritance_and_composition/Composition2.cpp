//: C14:Composition2.cpp
// Private embedded objects
#include "Useful.h"

class Y {
  int i;
  X x; // Embedded object
public:
  Y() { i = 0; }
  void f(int ii) { i = ii; x.set(ii); }
  int g() const { return i * x.read(); }
  void permute() { x.permute(); }
  auto read() { return x.read(); }
};

int main() {
  Y y;
  y.f(47);
  cout << "Y.i = " << y.g() << endl;
  y.permute();
  cout << "Y.x.i = " << y.read() << endl;
} ///:~

