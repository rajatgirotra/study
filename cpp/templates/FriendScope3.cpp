/*
One last option remains for using friends inside templates: fully define them inside the host class template definition itself. Here is how the previous example would appear with that change:
*/

//: C05:FriendScope3.cpp {-bor}
// Microsoft: use the -Za (ANSI-compliant) option
#include <iostream>
using namespace std;
 
template<class T> class Friendly {
  T t;
public:
  Friendly(const T& theT) : t(theT) {}
  friend void f(const Friendly<T>& fo) {
    cout << fo.t << endl;
  }
  void g() { f(*this); }
};
 
void h() {
  f(Friendly<int>(1));
}
 
int main() {
  h();
  Friendly<int>(2).g();
} ///:~
 
/*
There is an important difference between this and the previous example: f is not a template here, but is an ordinary function. (Remember that angle brackets were necessary before to imply that f( ) was a template.) Every time the Friendly class template is instantiated, a new, ordinary function overload is created that takes an argument of the current Friendly specialization. This is what Dan Saks has called making new friends.[68] This is the most convenient way to define friend functions for templates.
*/
