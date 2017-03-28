/*

Making everything an object
To prevent such resource leaks, you must guard against these .raw. resource allocations in one of two ways:

·      You can catch exceptions inside the constructor and then release the resource.

·      You can place the allocations inside an object.s constructor, and you can place the deallocations inside an object.s destructor.

Using the latter approach, each allocation becomes atomic, by virtue of being part of the lifetime of a local object, and if it fails, the other resource allocation objects are properly cleaned up during stack unwinding. This technique is called Resource Acquisition Is Initialization (RAII for short)  because it equates resource control with object lifetime. Using templates is an excellent way to modify the previous example to achieve this:

*/

//: C01:Wrapped.cpp
// Safe, atomic pointers.
#include <iostream>
#include <cstddef>
using namespace std;
 
// Simplified. Yours may have other arguments.
template<class T, int sz = 1> class PWrap {
  T* ptr;
public:
  class RangeError {}; // Exception class
  PWrap() {
    ptr = new T[sz];
    cout << "PWrap constructor" << endl;
  }
  ~PWrap() {
    delete[] ptr;
    cout << "PWrap destructor" << endl;
  }
  T& operator[](int i) throw(RangeError) {
    if(i >= 0 && i < sz) return ptr[i];
    throw RangeError();
  }
};
 
class Cat {
public:
  Cat() { cout << "Cat()" << endl; }
  ~Cat() { cout << "~Cat()" << endl; }
  void g() {}
};
 
class Dog {
public:
  void* operator new[](size_t) {
    cout << "Allocating a Dog" << endl;
    throw 47;
  }
  void operator delete[](void* p) {
    cout << "Deallocating a Dog" << endl;
    ::operator delete[](p);
  }
};
 
class UseResources {
  PWrap<Cat, 3> cats;
  PWrap<Dog> dog;
public:
  UseResources() { cout << "UseResources()" << endl; }
  ~UseResources() { cout << "~UseResources()" << endl; }
  void f() { cats[1].g(); }
};
 
int main() {
  try {
    UseResources ur;
  } catch(int) {
    cout << "inside handler" << endl;
  } catch(...) {
    cout << "inside catch(...)" << endl;
  }
} ///:~

/*
 
The difference is the use of the template to wrap the pointers and make them into objects. The constructors for these objects are called before the body of the UseResources constructor, and any of these constructors that complete before an exception is thrown will have their associated destructors called during stack unwinding.

The PWrap template shows a more typical use of exceptions than you.ve seen so far: A nested class called RangeError is created to use in operator[ ] if its argument is out of range. Because operator[ ] returns a reference, it cannot return zero. (There are no null references.) This is a true exceptional condition.you don.t know what to do in the current context and you can.t return an improbable value. In this example, RangeError[5] is simple and assumes all the necessary information is in the class name, but you might also want to add a member that contains the value of the index, if that is useful.

Now the output is

Cat()
Cat()
Cat()
PWrap constructor
allocating a Dog
~Cat()
~Cat()
~Cat()
PWrap destructor
inside handler
 
Again, the storage allocation for Dog throws an exception, but this time the array of Cat objects is properly cleaned up, so there is no memory leak.

*/
