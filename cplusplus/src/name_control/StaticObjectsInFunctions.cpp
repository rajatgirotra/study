//: C10:StaticObjectsInFunctions.cpp
#include <iostream>
using namespace std;

class X {
  int i;
public:
  X(int ii = 0) : i(ii) { cout<<"X::X()"<<endl; } // Default
  ~X() { cout << "X::~X()" << endl; }
};

void f() {
   static  X x1(47);
   //static X x2; // Default constructor required
}

int main() {
  f();
  cout<<"After call to function f()"<<endl;
} ///:~


/* 

Try removing the static keyword and compare the results in both the cases */

