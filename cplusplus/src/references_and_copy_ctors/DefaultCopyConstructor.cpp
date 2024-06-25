/*
   Default copy-constructor
   Because the copy-constructor implements pass and return by value, it.s important that the compiler creates one for you in the case of simple structures.
   When more complex types are involved, the C++ compiler will still automatically create a copy-constructor if you don.t make one. Again, however, a bitcopy doesn.t make sense, because it doesn.t necessarily implement the proper meaning.
   Here.s an example to show the more intelligent approach the compiler takes. Suppose you create a new class composed of objects of several existing classes. This is called, appropriately enough, composition, and it.s one of the ways you can make new classes from existing classes. Now take the role of a naive user who.s trying to solve a problem quickly by creating a new class this way. You don.t know about copy-constructors, so you don.t create one. The example demonstrates what the compiler does while creating the default copy-constructor for your new class:
 */

//: C11:DefaultCopyConstructor.cpp
// Automatic creation of the copy-constructor
#include <iostream>
#include <string>
using namespace std;

class WithCC { // With copy-constructor
   public:
      // Explicit default constructor required:
      WithCC() {}
      WithCC(const WithCC&) {
         cout << "WithCC(WithCC&)" << endl;
      }
};

class WoCC { // Without copy-constructor
   string id;
   public:
   WoCC(const string& ident = "") : id(ident) {}
   void print(const string& msg = "") const {
      if(msg.size() != 0) cout << msg << ": ";
      cout << id << endl;
   }
};

class Composite {
   WithCC withcc; // Embedded objects
   WoCC wocc;
   public:
   Composite() : wocc("Composite()") {}
   void print(const string& msg = "") const {
      wocc.print(msg);
   }
};

int main() {
   Composite c;
   c.print("Contents of c");
   cout << "Calling Composite copy-constructor"
      << endl;
   Composite c2 = c;  // Calls copy-constructor
   c2.print("Contents of c2");
} ///:~

/*
   To create a copy-constructor for a class that uses composition, the compiler recursively calls the copy-constructors for all the member objects and base classes. That is, if the member object also contains another object, its copy-constructor is also called. So in this case, the compiler calls the copy-constructor for WithCC. The output shows this constructor being called. Because WoCC has no copy-constructor, the compiler creates one for it that just performs a bitcopy, and calls that inside the Composite copy-constructor. The call to Composite::print( ) in main shows that this happens because the contents of c2.wocc are identical to the contents of c.wocc. The process the compiler goes through to synthesize a copy-constructor is called memberwise initialization.
   It's always best to create your own copy-constructor instead of letting the compiler do it for you. This guarantees that it will be under your control.
 */
