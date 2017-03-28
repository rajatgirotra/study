/*

Resource management
When writing code with exceptions, it.s particularly important that you always ask, .If an exception occurs, will my resources be properly cleaned up?. Most of the time you.re fairly safe, but in constructors there.s a particular problem: if an exception is thrown before a constructor is completed, the associated destructor will not be called for that object. Thus, you must be especially diligent while writing your constructor.

The difficulty is in allocating resources in constructors. If an exception occurs in the constructor, the destructor doesn.t get a chance to deallocate the resource. This problem occurs most often with .naked. pointers. For example:
*/

//: C01:Rawp.cpp
// Naked pointers.
#include <iostream>
#include <cstddef>
using namespace std;
 
class Cat {
public:
  Cat() { cout << "Cat()" << endl; }
  ~Cat() { cout << "~Cat()" << endl; }
};
 
class Dog {
public:
  void* operator new(size_t sz) {
    cout << "allocating a Dog" << endl;
    throw 47;
  }
  void operator delete(void* p) {
    cout << "deallocating a Dog" << endl;
    ::operator delete(p);
  }
};
 
class UseResources {
  Cat* bp;
  Dog* op;
public:
  UseResources(int count = 1) {
    cout << "UseResources()" << endl;
    bp = new Cat[count];
    op = new Dog;
  }
  ~UseResources() {
    cout << "~UseResources()" << endl;
    delete [] bp; // Array delete
    delete op;
  }
};
 
int main() {
  try {
    UseResources ur(3);
  } catch(int) {
    cout << "inside handler" << endl;
  }
} ///:~

/*
 
The output is

UseResources()
Cat()
Cat()
Cat()
allocating a Dog
inside handler
 
The UseResources constructor is entered, and the Cat constructor is successfully completed for the three array objects. However, inside Dog::operator new( ), an exception is thrown (to simulate an out-of-memory error). Suddenly, you end up inside the handler, without the UseResources destructor being called. This is correct because the UseResources constructor was unable to finish, but it also means the Cat objects that were successfully created on the heap were never destroyed.

*/
