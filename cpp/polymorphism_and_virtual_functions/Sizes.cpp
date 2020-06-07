/*

Please read Must_Read_1.txt first.

Storing type information

You can see that there is no explicit type information stored in any of the classes. But the previous examples, and simple logic, tell you that there must be some sort of type information stored in the objects; otherwise the type could not be established at runtime. This is true, but the type information is hidden. To see it, heres an example to examine the sizes of classes that use virtual functions compared with those that dont:

*/

//: C15:Sizes.cpp
// Object sizes with/without virtual functions
#include <iostream>
#include <cstddef>
using namespace std;

struct NoVirtual {
  int a;
public:
  void x() const {}
  int i() const { return 1; }
};

struct OneVirtual {
  int a;
public:
  virtual void x() const {}
  int i() const { return 1; }
};

struct TwoVirtuals {
  int a;
public:
  virtual void x() const {}
  virtual int i() const { return 1; }
};

int main() {
  cout << "int: " << sizeof(int) << endl;
  cout << "NoVirtual: "
       << sizeof(NoVirtual) << endl;
  cout << "void* : " << sizeof(void*) << endl;
  cout << "OneVirtual: "
       << sizeof(OneVirtual) << endl;
  cout << "TwoVirtuals: "
       << sizeof(TwoVirtuals) << endl;

  cout << offsetof(OneVirtual, a) << endl;
} ///:~

/*
 * Short answer: offsetof is a feature that is only in the C++ standard for legacy C compatibility. Therefore it is basically restricted to the stuff than can be done in C. C++ supports only what it must for C compatibility.

As offsetof is basically a hack (implemented as macro) that relies on the simple memory-model supporting C, it would take a lot of freedom away from C++ compiler implementors how to organize class instance layout.
*/
