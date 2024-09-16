/*

The other way to get runtime information for an object is through the typeid operator. This operator returns an object of class type_info, which yields information about the type of object to which it was applied. If the type is polymorphic, it gives information about the most derived type that applies (the dynamic type); otherwise it yields static type information. One use of the typeid operator is to get the name of the dynamic type of an object as a const char*, as you can see in the following example:

*/


//: C08:TypeInfo.cpp
// Illustrates the typeid operator.
#include <iostream>
#include <typeinfo>
using namespace std;
 
struct PolyBase { virtual ~PolyBase() {} };
struct PolyDer : PolyBase { PolyDer() {} };
struct NonPolyBase {};
struct NonPolyDer : NonPolyBase { NonPolyDer(int) {} };
 
int main() {
  // Test polymorphic Types
  const PolyDer pd;
  const PolyBase* ppb = &pd;
  cout << typeid(ppb).name() << endl;
  cout << typeid(*ppb).name() << endl;
  cout << boolalpha << (typeid(*ppb) == typeid(pd))
       << endl;
  cout << (typeid(PolyDer) == typeid(const PolyDer))
       << endl;
  // Test non-polymorphic Types
  const NonPolyDer npd(1);
  const NonPolyBase* nppb = &npd;
  cout << typeid(nppb).name() << endl;
  cout << typeid(*nppb).name() << endl;
  cout << (typeid(*nppb) == typeid(npd)) << endl;
  // Test a built-in type
  int i;
  cout << typeid(i).name() << endl;

  PolyBase* poPolyBase = 0;
  //cout<<typeid(*poPolyBase).name()<<endl;
} ///:~

/*
The output from this program using one particular compiler is
struct PolyBase const *
struct PolyDer
true
true
struct NonPolyBase const *
struct NonPolyBase
false
int
 

The first output line just echoes the static type of ppb because it is a pointer. To get RTTI to kick in, you need to look at the pointer or reference destination object, which is illustrated in the second line. Notice that RTTI ignores top-level const and volatile qualifiers. With non-polymorphic types, you just get the static type (the type of the pointer itself). As you can see, built-in types are also supported.

It turns out that you cant store the result of a typeid operation in a type_info object, because there are no accessible constructors and assignment is disallowed. You must use it as we have shown. In addition, the actual string returned by type_info::name( ) is compiler dependent. For a class named C, for example, some compilers return class C instead of just C (the cygwin compiler showed something else). Applying typeid to an expression that dereferences a null pointer will cause a bad_typeid exception (also defined in <typeinfo>) to be thrown.

*/
