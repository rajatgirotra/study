/*

You can also create static const objects of class types and arrays of such objects. However, you cannot initialize them using the inline syntax allowed for static consts of integral built-in types:

*/

//: C10:StaticObjectArrays.cpp
// Static arrays of class objects
class X {
  int i;
public:
  X(int ii) : i(ii) {}
};

class Stat {
  // This doesn't work, although 
  // you might want it to:
//!  static const X x(100);
  // Both const and non-const static class 
  // objects must be initialized externally:
  static X x2;
  static X xTable2[];
  static const X x3;
  static const X xTable3[];
};

X Stat::x2(100);

X Stat::xTable2[] = {
  X(1), X(2), X(3), X(4)
};

const X Stat::x3(100);

const X Stat::xTable3[] = {
  X(1), X(2), X(3), X(4)
};

int main() { Stat v; } ///:~

/*

The initialization of both const and non-const static arrays of class objects must be performed the same way, following the typical static definition syntax.

*/

