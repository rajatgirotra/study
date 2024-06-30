//: C14:Combined.cpp
// Inheritance & composition

#include <iostream>
using namespace std;

class A {
  int i;
public:
  A(int ii) : i(ii) { cout<<"A::A()"<<endl; }
  ~A() { cout<<"A::~A()"<<endl;}
  void f() const { cout<<"A::f()"<<endl;}
};

class B {
  int i;
public:
  B(int ii) : i(ii) {cout<<"B::B()"<<endl;}
  ~B() {cout<<"B::~B()"<<endl;}
  void f() const { cout<<"B::f()"<<endl;}
};

class C : public B {
  A a;
public:
  C(int ii) : B(ii), a(ii) { cout<<"C::C()"<<endl;}
  ~C() {cout<<"C::~C()"<<endl;} // Calls ~A() and ~B()
  void f() const {  // Redefinition
    a.f();
    B::f();
    cout<<"C::f()"<<endl;
  }
};

int main() {
  C c(47);
  c.f();
  return 0;
} ///:~

