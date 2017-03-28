/*
Read FriendScope*.cpp first

To clarify, suppose you want to add non-member friend operators to a class template. Here is a class template that simply holds a generic value:
template<class T> class Box {
  T t;
public:
  Box(const T& theT) : t(theT) {}
};
 

Without understanding the previous examples in this section, novices find themselves frustrated because they cant get a simple stream output inserter to work. If you dont define your operators inside the definition of Box, you must provide the forward declarations we showed earlier:
*/

//: C05:Box1.cpp
// Defines template operators.
#include <iostream>
using namespace std;
 
// Forward declarations
template<class T> class Box;
 
template<class T>
Box<T> operator+(const Box<T>&, const Box<T>&);
 
template<class T>
ostream& operator<<(ostream&, const Box<T>&);
 
template<class T> class Box {
  T t;
public:
  Box(const T& theT) : t(theT) {}
  friend Box operator+<>(const Box<T>&, const Box<T>&);
  friend ostream& operator<< <>(ostream&, const Box<T>&);
};
 
template<class T>
Box<T> operator+(const Box<T>& b1, const Box<T>& b2) {
  return Box<T>(b1.t + b2.t);
}
 
template<class T>
ostream& operator<<(ostream& os, const Box<T>& b) {
  return os << '[' << b.t << ']';
}
 
int main() {
  Box<int> b1(1), b2(2);
  cout << b1 + b2 << endl;  // [3]
  //cout << b1 + 2 << endl; // No implicit conversions!
} ///:~

