/*

References are like constant pointers that are automatically dereferenced by the compiler. 

They are essential in C++ to support the syntax of operator overloading, but they are also a general convenience to control the way arguments are passed into and out of functions.

The most important difference between pointers in C and those in C++ is that C++ is a more strongly typed language. This stands out where void* is concerned. C doesnt let you casually assign a pointer of one type to another, but it does allow you to accomplish this through a void*. Thus,

bird* b;
rock* r;
void* v;
v = r;
b = v;

Because this feature of C allows you to quietly treat any type like any other type, it leaves a big hole in the type system. C++ doesnt allow this; the compiler gives you an error message, and if you really want to treat one type as another, you must make it explicit, both to the compiler and to the reader

In line (1), the compiler allocates a piece of storage, initializes it with the value 12, and ties the reference to that piece of storage. The point is that any reference must be tied to someone elses piece of storage. When you access a reference, youre accessing that storage. Thus, if you write lines like (2) and (3), then incrementing a is actually incrementing x, as is shown in main( ). Again, the easiest way to think about a reference is as a fancy pointer. One advantage of this pointer is that you never have to wonder whether its been initialized (the compiler enforces it) and how to dereference it (the compiler does it).

*/


//: C11:FreeStandingReferences.cpp
#include <iostream>
using namespace std;

// Ordinary free-standing reference:
int y;
int& r = y;
// When a reference is created, it must 
// be initialized to a live object. 
// However, you can also say:
const int& q = 12;  // (1)
// References are tied to someone else's storage:
int x = 0;          // (2)
int& a = x;         // (3)
int main() {
  cout << "x = " << x << ", a = " << a << endl;
  a++;
  cout << "x = " << x << ", a = " << a << endl;
} ///:~

