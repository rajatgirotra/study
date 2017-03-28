/*

Constants in templates

Template arguments are not restricted to class types; you can also use built-in types. The values of these arguments then become compile-time constants for that particular instantiation of the template. You can even use default values for these arguments. The following example allows you to set the size of the Array class during instantiation, but also provides a default value:

*/

//: C16:Array3.cpp
// Built-in types as template arguments
#include "../require.h"
#include <iostream>
using namespace std;

template<class T, int size = 100>
class Array {
  T array[size];
public:
  T& operator[](int index) {
    require(index >= 0 && index < size,
      "Index out of range");
    return array[index];
  }
  int length() const { return size; }
};

class Number {
  float f;
public:
  Number(float ff = 0.0f) : f(ff) {}
  Number& operator=(const Number& n) {
    f = n.f;
    return *this;
  }
//  operator float() const { return f; }
  friend ostream&
    operator<<(ostream& os, const Number& x) {
      return os << x.f;
  }
};

template<class T, int size = 20>
class Holder {
  Array<T, size>* np;
public:
  Holder() : np(0) {}
  T& operator[](int i) {
    require(0 <= i && i < size);
    if(!np) np = new Array<T, size>;
    return np->operator[](i);
  }
  int length() const { return size; }
  ~Holder() { delete np; }
};

int main() {
  Holder<Number> h;
  for(int i = 0; i < 20; i++)
    h[i] = i; // This line calls the c'tor to create a Number object and then calls the assignment operator.
  for(int j = 0; j < 20; j++)
    cout << h[j] << endl;
} ///:~

/*


As before, Array is a checked array of objects and prevents you from indexing out of bounds. The class Holder is much like Array except that it has a pointer to an Array instead of an embedded object of type Array. This pointer is not initialized in the constructor; the initialization is delayed until the first access. This is called lazy initialization; you might use a technique like this if you are creating a lot of objects, but not accessing them all, and want to save storage.


Youll notice that the size value in both templates is never stored internally in the class, but it is used as if it were a data member inside the member functions.


*/
