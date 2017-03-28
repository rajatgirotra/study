/*
Now suppose that Friendly and f are both templates, as in the following program:
*/


//: C05:FriendScope2.cpp
#include <iostream>
using namespace std;
 
// Necessary forward declarations:
template<class T> class Friendly;
template<class T> void f(const Friendly<T>&);
 
template<class T> class Friendly {
  T t;
public:
  Friendly(const T& theT) : t(theT) {}
  friend void f<>(const Friendly<T>&);
  void g() { f(*this); }
};
 
void h() {
  f(Friendly<int>(1));
}
 
template<class T> void f(const Friendly<T>& fo) {
  cout << fo.t << endl;
}
 
int main() {
  h();
  Friendly<int>(2).g();
} ///:~
 
/*
First notice that angle brackets in the declaration of f inside Friendly. This is necessary to tell the compiler that f is a template. Otherwise, the compiler will look for an ordinary function named f and not find it. We could have inserted the template parameter (<T>) in the brackets, but it is easily deduced from the declaration.

The forward declaration of the function template f before the class definition is necessary, even though it wasnt in the previous example when f was a not a template; the language specifies that friend function templates must be previously declared. To properly declare f, Friendly must also have been declared, since f takes a Friendly argument, hence the forward declaration of Friendly in the beginning. We could have placed the full definition of f right after the initial declaration of Friendly instead of separating its definition and declaration, but we chose instead to leave it in a form that more closely resembles the previous example.
*/
