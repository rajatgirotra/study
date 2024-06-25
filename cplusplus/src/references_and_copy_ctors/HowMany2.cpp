/*

its possible to fix the problem in HowMany.cpp:

*/

//: C11:HowMany2.cpp
// The copy-constructor
#include <fstream>
#include <string>
using namespace std;
ofstream out("HowMany2.out");

class HowMany2 
{
  string name; // Object identifier
  static int objectCount;
public:
  HowMany2(const string& id = "") : name(id) {
    ++objectCount;
    print("HowMany2()");
  }

  ~HowMany2() {
    --objectCount;
    print("~HowMany2()");
  }

  // The copy-constructor:
  HowMany2(const HowMany2& h) : name(h.name) {
    name += " copy";
    ++objectCount;
    print("HowMany2(const HowMany2&)");
  }

  void print(const string& msg = "") const {
    if(msg.size() != 0) 
      out << msg << endl;
    out << '\t' << name << ": "
        << "objectCount = "
        << objectCount << endl;
  }
};

int HowMany2::objectCount = 0;

// Pass and return BY VALUE:
HowMany2 f(HowMany2 x) {
  x.print("x argument inside f()");
  out << "Returning from f()" << endl;
  return x;
}

int main() {
  HowMany2 h("h");
  out << "Entering f()" << endl;
  HowMany2 h2 = f(h);
  h2.print("h2 after call to f()");
  out << "Call f(), no return value" << endl;
  f(h);
  out << "After call to f()" << endl;
} ///:~

/*
There are a number of new twists thrown in here so you can get a better idea of whats happening. First, the string name acts as an object identifier when information about that object is printed. In the constructor, you can put an identifier string (usually the name of the object) that is copied to name using the string constructor. The default = "" creates an empty string. The constructor increments the objectCount as before, and the destructor decrements it.


Next is the copy-constructor, HowMany2(const HowMany2&). The copy-constructor can create a new object only from an existing one, so the existing objects name is copied to name, followed by the word copy so you can see where it came from. If you look closely, youll see that the call name(h.name) in the constructor initializer list is actually calling the string copy-constructor.


Inside the copy-constructor, the object count is incremented just as it is inside the normal constructor. This means youll now get an accurate object count when passing and returning by value.


The print( ) function has been modified to print out a message, the object identifier, and the object count. It must now access the name data of a particular object, so it can no longer be a static member function.


Inside main( ), you can see that a second call to f( ) has been added. However, this call uses the common C approach of ignoring the return value. But now that you know how the value is returned (that is, code inside the function handles the return process, putting the result in a destination whose address is passed as a hidden argument), you might wonder what happens when the return value is ignored. The output of the program will throw some illumination on this.

*/

