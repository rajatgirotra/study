/*

static member functions
You can also create static member functions that, like static data members, work for the class as a whole rather than for a particular object of a class.
 Instead of making a global function that lives in and pollutes the global or local namespace, you bring the function inside the class. When you create a static member function,
 you are expressing an association with a particular class.
You can call a static member function in the ordinary way, with the dot or the arrow, in association with an object. However, its more typical to call a static member function by itself, without any specific object, using the scope-resolution operator, like this:

//: C10:SimpleStaticMemberFunction.cpp
class X {
public:
  static void f(){};
};

int main() {
  X::f();
} ///:~
When you see static member functions in a class, remember that the designer intended that function to be conceptually associated with the class as a whole.
A static member function cannot access ordinary data members, only static data members. It can call only other static member functions. Normally, the address of the current object (this)
 is quietly passed in when any member function is called, but a static member has no this, which is the reason it cannot access ordinary members. Thus, you get the tiny increase in speed afforded by a global function
 because a static member function doesn't have the extra overhead of passing this. At the same time you get the benefits of having the function inside the class.
For data members, static indicates that only one piece of storage for member data exists for all objects of a class. This parallels the use of static to define objects inside a function to mean that only one copy of a local variable is used for all calls of that function.
Here's an example showing static data members and static member functions used together:

*/


//: C10:StaticMemberFunctions.cpp
class X {
  int i;
  static int j;
public:
  X(int ii = 0) : i(ii) {
     // Non-static member function can access
     // static member function or data:
    j = i;
  }
  int val() const { return i; }
  static int incr() {
    //! i++; // Error: static member function
    // cannot access non-static member data
    return ++j;
  }
  static int f() {
    //! val(); // Error: static member function
    // cannot access non-static member function
    return incr(); // OK -- calls static
  }
};

int X::j = 0;

int main() {
  X x;
  X* xp = &x;
  x.f();
  xp->f();
  X::f(); // Only works with static members
} ///:~

