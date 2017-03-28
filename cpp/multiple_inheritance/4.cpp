/*

What we usually want in such cases is true diamond inheritance, where a single Top object is shared by both Left and Right subobjects within a complete Bottom object, which is what the first class diagram depicts. This is achieved by making Top a virtual base class of Left and Right:

*/


//: C09:VirtualBase.cpp
// Shows a shared subobject via a virtual base.
#include <iostream>
using namespace std;
 
class Top {
protected:
  int x;
public:
  Top(int n) { x = n; }
  virtual ~Top() {}
  friend ostream&
  operator<<(ostream& os, const Top& t) {
    return os << t.x;
  }
};
 
class Left : virtual public Top {
protected:
  int y;
public:
  Left(int m, int n) : Top(m) { y = n; }
};
 
class Right : virtual public Top {
protected:
  int z;
public:
  Right(int m, int n) : Top(m) { z = n; }
};
 
class Bottom : public Left, public Right {
  int w;
public:
  Bottom(int i, int j, int k, int m)
  : Top(i), Left(-98, j), Right(747, k) { w = m; }
  friend ostream&
  operator<<(ostream& os, const Bottom& b) {
    return os << b.x << ',' << b.y << ',' << b.z
      << ',' << b.w;
  }
};
 
int main() {
  cout<<"Size of Top " <<sizeof(Top)<<endl;
  cout<<"Size of Left " <<sizeof(Left)<<endl;
  cout<<"Size of Right " <<sizeof(Right)<<endl;
  Bottom b(1, 2, 3, 4);
  cout << sizeof b << endl;
  cout << b << endl;
  cout << static_cast<void*>(&b) << endl;
  Top* p = static_cast<Top*>(&b); // This makes p point to the top subobject which is at the end of the complete subobject.
  cout << *p << endl;
  cout << static_cast<void*>(p) << endl;
  cout << dynamic_cast<void*>(p) << endl; // The result of a dynamic_cast to void* always resolves to the address of the complete object.
} ///:~

/*

Each virtual base of a given type refers to the same object, no matter where it appears in the hierarchy.[126] This means that when a Bottom object is instantiated, the object layout may look something like this:

The Left and Right subobjects each have a pointer (or some conceptual equivalent) to the shared Top subobject, and all references to that subobject in Left and Right member functions will go through those these pointers.[127] Here, there is no ambiguity when upcasting from a Bottom to a Top object, since there is only one Top object to convert to.

The output of the previous program is as follows:
36
1,2,3,4
1245032
1
1245060
1245032

The addresses printed suggest that this particular implementation does indeed store the Top subobject at the end of the complete object (although its not really important where it goes). The result of a dynamic_cast to void* always resolves to the address of the complete object.

Although it is technically illegal to do so[128], if you remove the virtual destructor (and the dynamic_cast statement, so the program will compile), the size of Bottom decreases to 24 bytes. That seems to be a decrease equivalent to the size of three pointers. Why?

Its important not to take these numbers too literally. Other compilers we use manage only to increase the size by four bytes when the virtual constructor is added. Not being compiler writers, we cant tell you their secrets. We can tell you, however, that with multiple inheritance, a derived object must behave as if it has multiple VPTRs, one for each of its direct base classes that also have virtual functions. Its as simple as that. Compilers make whatever optimizations their authors invent, but the behavior must be the same.

The strangest thing in the previous code is the initializer for Top in the Bottom constructor. Normally one doesnt worry about initializing subobjects beyond direct base classes, since all classes take care of initializing their own bases. There are, however, multiple paths from Bottom to Top, so relying on the intermediate classes Left and Right to pass along the necessary initialization data results in an ambiguitywho is responsible for performing the initialization? For this reason, the most derived class must initialize a virtual base. But what about the expressions in the Left and Right constructors that also initialize Top? They are certainly necessary when creating standalone Left or Right objects, but must be ignored when a Bottom object is created (hence the zeros in their initializers in the Bottom constructorany values in those slots are ignored when the Left and Right constructors execute in the context of a Bottom object). The compiler takes care of all this for you, but its important to understand where the responsibility lies. Always make sure that all concrete (nonabstract) classes in a multiple inheritance hierarchy are aware of any virtual bases and initialize them appropriately.
*/
