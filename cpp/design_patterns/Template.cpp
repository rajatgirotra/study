/*

Template Method

An application framework allows you to inherit from a class or set of classes and create a new application, reusing most of the code in the existing classes and overriding one or more functions in order to customize the application to your needs. A fundamental concept in the application framework is the Template Method, which is typically hidden beneath the covers and drives the application by calling the various functions in the base class (some of which you have overridden in order to create the application).

An important characteristic of the Template Method is that it is defined in the base class (sometimes as a private member function) and cannot be changedthe Template Method is the thing that stays the same. It calls other base-class functions (the ones you override) in order to do its job, but the client programmer isnt necessarily able to call it directly, as you can see here:

*/


//: C10:TemplateMethod.cpp
// Simple demonstration of Template Method.
#include <iostream>
using namespace std;
 
class ApplicationFramework {
protected:
  virtual void customize1() = 0;
  virtual void customize2() = 0;
public:
  void templateMethod() {
    for(int i = 0; i < 5; i++) {
      customize1();
      customize2();
    }
  }
};
 
// Create a new "application":
class MyApp : public ApplicationFramework {
protected:
  void customize1() { cout << "Hello "; }
  void customize2() { cout << "World!" << endl; }
};
 
int main() {
  MyApp app;
  app.templateMethod();
} ///:~

