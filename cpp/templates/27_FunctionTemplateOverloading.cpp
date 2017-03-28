/*

Function template overloading

As with ordinary functions, you can overload function templates that have the same name. When the compiler processes a function call in a program, it has to decide which template or ordinary function is the best fit for the call. Along with the min( ) function template introduced earlier, lets add some ordinary functions to the mix:

*/


//: C05:MinTest.cpp
#include <cstring>
#include <iostream>
using std::strcmp;
using std::cout;
using std::endl;
 
template<typename T> const T& min(const T& a, const T& b) {
  return (a < b) ? a : b;
}
 
const char* min(const char* a, const char* b) {
  return (strcmp(a, b) < 0) ? a : b;
}
 
double min(double x, double y) {
  return (x < y) ? x : y;
}
 
int main() {
  const char *s2 = "say \"Ni-!\"", *s1 = "knights who";
  cout << min(1, 2) << endl;      // 1: 1 (template)
  cout << min(1.0, 2.0) << endl;  // 2: 1 (double)
  cout << min(1, 2.0) << endl;    // 3: 1 (double)
  cout << min(s1, s2) << endl;    // 4: knights who (const
                                  //                 char*)
  cout << min<>(s1, s2) << endl;  // 5: say "Ni-!"
                                  //    (template)

} ///:~

/*
 

In addition to the function template, this program defines two non-template functions: a C-style string version of min( ) and a double version. If the template doesnt exist, the call in line 1 above invokes the double version of min( ) because of the standard conversion from int to double. The template can generate an int version which is considered a better match, so thats what happens. The call in line 2 is an exact match for the double version, and the call in line 3 also invokes the same function, implicitly converting 1 to 1.0. In line 4 the const char* version of min( ) is called directly. In line 5 we force the compiler to use the template facility by appending empty angle brackets to the function name, whereupon it generates a const char* version from the template and uses it (which is verified by the wrong answerits just comparing addresses![54]). If youre wondering why we have using declarations in lieu of the using namespace std directive, its because some compilers include headers behind the scenes that bring in std::min( ), which would conflict with our declarations of the name min( ).

As stated above, you can overload templates of the same name, as long as they can be distinguished by the compiler. You could, for example, declare a min( ) function template that processes three arguments:
template<typename T>
const T& min(const T& a, const T& b, const T& c);
 

Versions of this template will be generated only for calls to min( ) that have three arguments of the same type.

*/
