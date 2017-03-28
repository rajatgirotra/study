/*

The reference argument in Reference.cpp works only when the argument is a non-const object. If it is a const object, the function g( ) will not accept the argument, which is actually a good thing, because the function does modify the outside argument. If you know the function will respect the constness of an object, making the argument a const reference will allow the function to be used in all situations. This means that, for built-in types, the function will not modify the argument, and for user-defined types, the function will call only const member functions, and wont modify any public data members.

The use of const references in function arguments is especially important because your function may receive a temporary object. This might have been created as a return value of another function or explicitly by the user of your function. Temporary objects are always const, so if you dont use a const reference, that argument wont be accepted by the compiler. As a very simple example,

*/


//: C11:ConstReferenceArguments.cpp
// Passing references as const

#include <iostream>
using namespace std;

void f(int&) {}
void g(const int&) {}

int main() {
//!  f(1); // Error
  g(1);
  return 0;
} ///:~

