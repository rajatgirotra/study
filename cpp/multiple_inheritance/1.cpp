/*

One use of multiple inheritance that is not controversial pertains to interface inheritance. In C++, all inheritance is implementation inheritance, because everything in a base class, interface and implementation, becomes part of a derived class. It is not possible to inherit only part of a class (the interface alone, say). As Chapter 14 of Volume 1 explains, private and protected inheritance make it possible to restrict access to members inherited from base classes when used by clients of a derived class object, but this doesnt affect the derived class; it still contains all base class data and can access all non-private base class members.

Interface inheritance, on the other hand, only adds member function declarations to a derived class interface and is not directly supported in C++. The usual technique to simulate interface inheritance in C++ is to derive from an interface class, which is a class that contains only declarations (no data or function bodies). These declarations will be pure virtual functions, except for the destructor. Here is an example:

*/

// Multiple interface inheritance.
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
 
class Printable {
public:
  virtual ~Printable() {}
  virtual void print(ostream&) const = 0;
};
 
class Intable {
public:
  virtual ~Intable() {}
  virtual int toInt() const = 0;
};
 
class Stringable {
public:
  virtual ~Stringable() {}
  virtual string toString() const = 0;
};
 
class Able : public Printable, public Intable,
             public Stringable {
  int myData;
public:
  Able(int x) { myData = x; }
  void print(ostream& os) const { os << myData; }
  int toInt() const { return myData; }
  string toString() const {
    ostringstream os;
    os << myData;
    return os.str();
  }
};
 
void testPrintable(const Printable& p) {
  p.print(cout);
  cout << endl;
}
 
void testIntable(const Intable& n) {
  cout << n.toInt() + 1 << endl;
}
 
void testStringable(const Stringable& s) {
  cout << s.toString() + "th" << endl;
}
 
int main() {
  Able a(7);
  testPrintable(a);
  testIntable(a);
  testStringable(a);
} ///:~

/* 

The class Able implements the interfaces Printable, Intable, and Stringable because it provides implementations for the functions they declare. Because Able derives from all three classes, Able objects have multiple is-a relationships. For example, the object a can act as a Printable object because its class, Able, derives publicly from Printable and provides an implementation for print( ). The test functions have no need to know the most-derived type of their parameter; they just need an object that is substitutable for their parameters type.

*/
