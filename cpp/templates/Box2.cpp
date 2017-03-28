//: C05:Box2.cpp
// Defines non-template operators.
#include <iostream>
using namespace std;
 
template<class T> class Box {
  T t;
public:
  Box(const T& theT) : t(theT) {}
  friend Box<T> operator+(const Box<T>& b1,
                          const Box<T>& b2) {
    return Box<T>(b1.t + b2.t);
  }
  friend ostream&
  operator<<(ostream& os, const Box<T>& b) {
    return os << '[' << b.t << ']';
  }
};
 
int main() {
  Box<int> b1(1), b2(2);
  cout << b1 + b2 << endl; // [3]
  cout << b1 + 2 << endl; // [3]
} ///:~

/*
Because the operators are normal functions (overloaded for each specialization of Boxjust int in this case), implicit conversions are applied as normal; so the expression b1 + 2 is valid.

Note that theres one type in particular that cannot be made a friend of Box, or any other class template for that matter, and that type is Tor rather, the type that the class template is parameterized upon. To the best of our knowledge, there are really no good reasons why this shouldnt be allowed, but as is, the declaration friend class T is illegal, and should not compile.
*/
