//: C14:NameHiding.cpp
// Hiding overloaded names during inheritance
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
  int f() const { 
    cout << "Base::f()\n"; 
    return 1; 
  }
  int f(string) const {  cout<<"Base::f(string)"<<endl; return 1; }
  void g() { cout<<"Base::g()"<<endl; }
};

class Derived1 : public Base {
public:
  void g() const { cout<<"Derived1::g()"<<endl; }
};

class Derived2 : public Base {
public:
  // Redefinition:
  int f() const { 
    cout << "Derived2::f()\n"; 
    return 2;
  }
};

class Derived3 : public Base {
public:
  // Change return type:
  void f() const { cout << "Derived3::f()\n"; }
};

class Derived4 : public Base {
public:
  // Change argument list:
  int f(int) const { 
    cout << "Derived4::f()\n"; 
    return 4; 
  }
};

int main() {
  string s("hello");
  [[maybe_unused]] int x;

  Derived1 d1;
  x = d1.f();
  d1.f(s);
  d1.g();

  #if 1
  Derived2 d2;
  x = d2.f();
//  d2.f(s);  //string version hidden
  d2.g();
  #endif

  [[maybe_unused]] Derived3 d3;
 // d3.f(s);    // Both the inherited versions of f() are hidden if we change the return type of the function
  //x = d3.f(); // return int version hidden

  Derived4 d4;
  d4.g(); // Both f() versions in Base are hidden if you overload the function.
  x = d4.f(1);
  return 0;
} ///:~

