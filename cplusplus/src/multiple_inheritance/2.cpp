/*
When you inherit from a base class, you get a copy of all the data members of that base class in your derived class. The following program shows how multiple base subobjects might be laid out in memory:
*/

//: C09:Offset.cpp
// Illustrates layout of subobjects with MI.
#include <iostream>
using namespace std;
 
class A { int x; };
class B { int y; };
class C : public A, public B { int z; };
 
int main() {
  cout << "sizeof(A) == " << sizeof(A) << endl;
  cout << "sizeof(B) == " << sizeof(B) << endl;
  cout << "sizeof(C) == " << sizeof(C) << endl;

  C c;
  cout << "&c == " << static_cast<void*>(&c) << endl;

  A* ap = &c;
  B* bp = &c;

  cout << "ap == " << static_cast<void*>(ap) << endl;
  cout << "bp == " << static_cast<void*>(bp) << endl;
  C* cp = static_cast<C*>(bp);
  cout << "cp == " << static_cast<void*>(cp) << endl;
  cout << "bp == cp? " << boolalpha << (bp == cp) << endl;
  cp = 0;
  bp = cp;
  cout << bp << endl;
  cp = &c;
  bp = cp;
  cout<<static_cast<void*>(bp)<<endl;

  B *poB = new B;                       // These statements are illegal but not detected as an error. dynamic_cast<> can solve the problem.
 // A *poA = new A;                       // These statements are illegal but not detected as an error. dynamic_cast<> can solve the problem.
  cout<<static_cast<void*>(poB)<<endl;
  C* cp1 = static_cast<C*>(poB);
  cout<<static_cast<void*>(cp1)<<endl; // This prints 4 bytes less than the previous print.
/*

This happens because static_cast assumes that the C object has A's data, then B's data then C's data. So it moves back 4 bytes thinking that it is now pointing to the complete C object. If class A had not been there; then it would not have moved back 4 bytes. The bottom line is: Avoid using static_cast<> with class heirarchies. Use dynamic_cast<> instead.

*/

	B* b = 0;
        C* poC = static_cast<C*>(b);
        cout<<static_cast<void*>(poC)<<endl;  //Nulls are treated differently as explained below.


}

/*

Output:
sizeof(A) == 4
sizeof(B) == 4
sizeof(C) == 12
&c == 1245052
ap == 1245052
bp == 1245056
cp == 1245052
bp == cp? true
0
 

As you can see, the B portion of the object c is offset 4 bytes from the beginning of the entire object, suggesting the following layout:

                               1245052  --------------
                                       |              |
                                       |              |
                                       |  A's Data    |
                                       |              |
                                       |              |
                               1245056  --------------
                                       |              |
                                       |              |
                                       |  B's Data    |
                                       |              |
                                       |              |
                               1245060  --------------
                                       |              |
                                       |              |
                                       |  C's Data    |
                                       |              |
                                       |              |
                                        --------------


The object c begins with its A subobject, then the B portion, and finally the data from the complete type C itself. Since a C is-an A and is-a B, it is possible to upcast to either base type. When upcasting to an A, the resulting pointer points to the A portion, which happens to be at the beginning of the C object, so the address ap is the same as the expression &c. When upcasting to a B, however, the resulting pointer must point to where the B subobject actually resides because class B knows nothing about class C (or class A, for that matter). In other words, the object pointed to by bp must be able to behave as a standalone B object (except for any required polymorphic behavior).

When casting bp back to a C*, since the original object was a C in the first place, the location where the B subobject resides is known, so the pointer is adjusted back to the original address of the complete object. If bp had been pointing to a standalone B object instead of a C object in the first place, the cast would be illegal.[124] Furthermore, in the comparison bp == cp, cp is implicitly converted to a B*, since that is the only way to make the comparison meaningful (that is, upcasting is always allowed), hence the true result. So when converting back and forth between subobjects and complete types, the appropriate offset is applied.

The null pointer requires special handling, obviously, since blindly subtracting an offset when converting to or from a B subobject will result in an invalid address if the pointer was zero to start with. For this reason, when casting to or from a B*, the compiler generates logic to check first to see if the pointer is zero. If it isnt, it applies the offset; otherwise, it leaves it as zero.

*/
