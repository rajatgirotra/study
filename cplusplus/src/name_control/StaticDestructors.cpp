/*
Like ordinary destruction, destruction of static objects occurs in the reverse order of initialization. However, only objects that have been constructed are destroyed.
 Fortunately, the C++ development tools keep track of initialization order and the objects that have been constructed. Global objects are always constructed before main()
 is entered and destroyed as main() exits, but if a function containing a local static object is never called, the constructor for that object is never executed,
 so the destructor is also not executed. For example,
*/

//: C10:StaticDestructors.cpp
// Static object destructors
#include <fstream>
using namespace std;
ofstream out("statdest.out"); // Trace file

class Obj {
  char c; // Identifier
public:
  Obj(char cc) : c(cc) {
    out << "Obj::Obj() for " << c << endl;
  }
  ~Obj() {
    out << "Obj::~Obj() for " << c << endl;
  }
};

Obj a('a'); // Global (static storage)
// Constructor & destructor always called

void f() {
  static Obj b('b');
}

void g() {
  static Obj c('c');
}

int main() {
  out << "inside main()" << endl;
  f(); // Calls static constructor for b
  // g() not called
  out << "leaving main()" << endl;
} ///:~

/*

In C++, the constructor for a global static object is called before main( ) is entered, so you now have a simple and portable way to execute code before entering main( ) and to execute code with the destructor after exiting main( ). In C, this was always a trial that required you to root around in the compiler vendors assembly-language startup code.

*/
