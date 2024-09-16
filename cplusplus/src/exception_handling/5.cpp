/*

Exception matching
When an exception is thrown, the exception-handling system looks through the .nearest. handlers in the order they appear in the source code. When it finds a match, the exception is considered handled and no further searching occurs.

Matching an exception doesn.t require a perfect correlation between the exception and its handler. An object or reference to a derived-class object will match a handler for the base class. (However, if the handler is for an object rather than a reference, the exception object is .sliced..truncated to the base type.as it is passed to the handler. This does no damage, but loses all the derived-type information.) For this reason, as well as to avoid making yet another copy of the exception object, it is always better to catch an exception by reference instead of by value.[3] If a pointer is thrown, the usual standard pointer conversions are used to match the exception. However, no automatic type conversions are used to convert from one exception type to another in the process of matching. For example:
*/

//: C01:Autoexcp.cpp
// No matching conversions.
#include <iostream>
using namespace std;
 
class Except1 {};
 
class Except2 {
public:
  Except2(const Except1&) {}
};
 
void f() { throw Except1(); }
 
int main() {
  try { f();
  } catch(Except2&) {
    cout << "inside catch(Except2)" << endl;
  } catch(Except1&) {
    cout << "inside catch(Except1)" << endl;
  }
} ///:~

/*
 
Even though you might think the first handler could be matched by converting an Except1 object into an Except2 using the converting constructor, the system will not perform such a conversion during exception handling, and you.ll end up at the Except1 handler.

The following example shows how a base-class handler can catch a derived-class exception:

*/
