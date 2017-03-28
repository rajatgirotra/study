/*

Normally, a pure virtual function in a base class would cause the derived class to be abstract unless it (and all other pure virtual functions) is given a definition. But here, this seems not to be the case. However, remember that the compiler automatically creates a destructor definition for every class if you dont create one. Thats whats happening here  the base class destructor is being quietly overridden, and thus the definition is being provided by the compiler and Derived is not actually abstract.


This brings up an interesting question: What is the point of a pure virtual destructor? Unlike an ordinary pure virtual function, you must give it a function body. In a derived class, you arent forced to provide a definition since the compiler synthesizes the destructor for you. So whats the difference between a regular virtual destructor and a pure virtual destructor?


The only distinction occurs when you have a class that only has a single pure virtual function: the destructor. In this case, the only effect of the purity of the destructor is to prevent the instantiation of the base class. If there were any other pure virtual functions, they would prevent the instantiation of the base class, but if there are no others, then the pure virtual destructor will do it. So, while the addition of a virtual destructor is essential, whether its pure or not isnt so important.


When you run the following example, you can see that the pure virtual function body is called after the derived class version, just as with any other destructor:

*/

//: C15:PureVirtualDestructors.cpp
// Pure virtual destructors
// require a function body
#include <iostream>
using namespace std;

class Pet {
public:
  virtual ~Pet() = 0;
};


Pet::~Pet() {
  cout << "~Pet()" << endl;
}

class Dog : public Pet {
public:
  ~Dog() {
    cout << "~Dog()" << endl;
  }
};

int main() {
  Pet* p = new Dog; // Upcast
  delete p; // Virtual destructor call
  //Pet objP;
} ///:~

