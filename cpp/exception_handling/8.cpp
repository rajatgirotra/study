/*

Cleaning up
Part of the magic of exception handling is that you can pop from normal program flow into the appropriate exception handler. Doing so wouldn.t be useful, however, if things weren.t cleaned up properly as the exception was thrown. C++ exception handling guarantees that as you leave a scope, all objects in that scope whose constructors have been completed will have their destructors called.

Here.s an example that demonstrates that constructors that aren.t completed don.t have the associated destructors called. It also shows what happens when an exception is thrown in the middle of the creation of an array of objects:

*/

//: C01:Cleanup.cpp
// Exceptions clean up complete objects only.
#include <iostream>
using namespace std;
 
class Trace {
  static int counter;
  int objid;
public:
  Trace() {
    objid = counter++;
    cout << "constructing Trace #" << objid << endl;
    if(objid == 3) throw 3;
  }
  ~Trace() {
    cout << "destructing Trace #" << objid << endl;
  }
};
 
int Trace::counter = 0;
 
int main() {
  try {
    Trace n1;
    // Throws exception:
    Trace array[5];
    Trace n2;  // Won't get here.
  } catch(int& i) {
    cout << "caught " << i << endl;
  }
} ///:~

/*

The class Trace keeps track of objects so that you can trace program progress. It keeps a count of the number of objects created with a static data member counter and tracks the number of the particular object with objid.

The main program creates a single object, n1 (objid 0), and then attempts to create an array of five Trace objects, but an exception is thrown before the fourth object (#3) is fully created. The object n2 is never created. You can see the results in the output of the program:

constructing Trace #0
constructing Trace #1
constructing Trace #2
constructing Trace #3
destructing Trace #2
destructing Trace #1
destructing Trace #0
caught 3
 
Three array elements are successfully created, but in the middle of the constructor for the fourth element, an exception is thrown. Because the fourth construction in main( ) (for array[2]) never completes, only the destructors for objects array[1] and array[0] are called. Finally, object n1 is destroyed, but not object n2, because it was never created.

*/
