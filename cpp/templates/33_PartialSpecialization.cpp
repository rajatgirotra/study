/*

Class templates can also be partially specialized, meaning that at least one of the template parameters is left open in some way in the specialization. vector<bool> specifies the object type (bool), but leaves the allocator type unspecified. Here is the actual declaration of vector<bool>:
template<class Allocator> class vector<bool, Allocator>;
 

You can recognize a partial specialization because non-empty parameter lists appear in angle brackets both after the template keyword (the unspecified parameters) and after the class (the specified arguments). Because of the way vector<bool> is defined, a user can provide a custom allocator type, even though the contained type of bool is fixed. In other words, specialization, and partial specialization in particular, constitute a sort of overloading for class templates.
Partial ordering of class templates

The rules that determine which template is selected for instantiation are similar to the partial ordering for function templatesthe most specialized template is selected. The string in each f( ) member function in the illustration below explains the role of each template definition:

*/


//: C05:PartialOrder2.cpp
// Reveals partial ordering of class templates.
#include <iostream>
using namespace std;
 
template<class T, class U> class C {
public:
  void f() { cout << "Primary Template\n"; }
};
 
template<class U> class C<int, U> {
public:
  void f() { cout << "T == int\n"; }
};
 
template<class T> class C<T, double> {
public:
  void f() { cout << "U == double\n"; }
};
 
template<class T, class U> class C<T*, U> {
public:
  void f() { cout << "T* used\n"; }
};
 
template<class T, class U> class C<T, U*> {
public:
  void f() { cout << "U* used\n"; }
};
 
template<class T, class U> class C<T*, U*> {
public:
  void f() { cout << "T* and U* used\n"; }
};
 
template<class T> class C<T, T> {
public:
  void f() { cout << "T == U\n"; }
};
 
int main() {
  C<float, int>().f();    // 1: Primary template
  C<int, float>().f();    // 2: T == int
  C<float, double>().f(); // 3: U == double
  C<float, float>().f();  // 4: T == U
  C<float*, float>().f(); // 5: T* used [T is float]
  C<float, float*>().f(); // 6: U* used [U is float]
  C<float*, int*>().f();  // 7: T* and U* used [float,int]
  // The following are ambiguous:
//   8: C<int, int>().f();
//   9: C<double, double>().f();
//  10: C<float*, float*>().f();
//  11: C<int, int*>().f();
//  12: C<int*, int*>().f();
} ///:~

/*

As you can see, you can partially specify template parameters according to whether they are pointer types, or whether they are equal. When the T* specialization is used, such as is the case in line 5, T itself is not the top-level pointer type that was passedit is the type that the pointer refers to (float, in this case). The T* specification is a pattern to allow matching against pointer types. If you use int** as the first template argument, T becomes int*. Line 8 is ambiguous because having the first parameter as an int versus having the two parameters equal are independent issuesone is not more specialized than the other. Similar logic applies to lines 9 through 12.

*/
