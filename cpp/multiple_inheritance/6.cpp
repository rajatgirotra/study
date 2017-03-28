/*

Having discussed virtual base classes, we can now illustrate the full story of object initialization. Since virtual bases give rise to shared subobjects, it makes sense that they should be available before the sharing takes place. So the order of initialization of subobjects follows these rules, recursively:

1.      All virtual base class subobjects are initialized, in top-down, left-to-right order according to where they appear in class definitions.

2.      Non-virtual base classes are then initialized in the usual order.

3.      All member objects are initialized in declaration order.

4.      The complete objects constructor executes.

The following program illustrates this behavior:

*/

//: C09:VirtInit.cpp
// Illustrates initialization order with virtual bases.
#include <iostream>
#include <string>
using namespace std;
 
class M {
public:
  M(const string& s) { cout << "M " << s << endl; }
};
 
class A {
  M m;
public:
  A(const string& s) : m("in A") {
    cout << "A " << s << endl;
  }
  virtual ~A() {}
};
 
class B {
  M m;
public:
  B(const string& s) : m("in B")  {
    cout << "B " << s << endl;
  }
  virtual ~B() {}
};
 
class C {
  M m;
public:
  C(const string& s) : m("in C")  {
    cout << "C " << s << endl;
  }
  virtual ~C() {}
};
 
class D {
  M m;
public:
  D(const string& s) : m("in D") {
    cout << "D " << s << endl;
  }
  virtual ~D() {}
};
 
class E : public A, virtual public B, virtual public C {
  M m;
public:
  E(const string& s) : C("from E"), A("from E"),
  B("from E"), m("in E") {
    cout << "E " << s << endl;
  }
};
 
class F : virtual public C, virtual public B, public D {
  M m;
public:
  F(const string& s) : B("from F"), C("from F"),
  D("from F"), m("in F") {
    cout << "F " << s << endl;
  }
};
 
class G : public E, public F {
  M m;
public:
  G(const string& s) : B("from G"), C("from G"),
  E("from G"),  F("from G"), m("in G") {
    cout << "G " << s << endl;
  }
};
 
int main() {
  G g("from main");
} ///:~


