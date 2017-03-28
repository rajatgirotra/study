/*

With the syntax weve seen so far, if you have multiple base classes, and if those base classes in turn have a common base class, you will have two copies of the top-level base, as you can see in the following example:

*/


//: C09:Duplicate.cpp
// Shows duplicate subobjects.
#include <iostream>
using namespace std;
 
class Top {
public:
  int x;
  Top(int n) { x = n; }
};
 
class Left : public Top {
public:
  int y;
  Left(int m, int n) : Top(m) { y = n; }
};
 
class Right : public Top {
public:
  int z;
  Right(int m, int n) : Top(m) { z = n; }
};
 
class Bottom : public Left, public Right {
public:
  int w;
  Bottom(int i, int j, int k, int m)
  : Left(i, k), Right(j, k) { w = m; }
};
 
int main() {
  Bottom b(1, 2, 3, 4);
  cout << sizeof b << endl; // 20
//  cout << "Top.x = " << b.x << endl;  //--> Errorneous line, Top::x is ambiguous.
//  cout << "Top.y = " << b.y << endl; //This is OK.
//   Top* poTop = new Bottom(1, 2, 3, 4); //--> Errorneous line, Top is an ambiguous Base of Bottom.
} ///:~

/* 

Since the size of b is 20 bytes,[125] there are five integers altogether in a complete Bottom object.

*/
