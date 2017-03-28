/*

static array initialization

Chapter 8 introduced the static const variable that allows you to define a constant value inside a class body. Its also possible to create arrays of static objects, both const and non-const. The syntax is reasonably consistent:

*/


//: C10:StaticArray.cpp
// Initializing static arrays in classes
class Values {
  // static consts are initialized in-place:
  static const int scSize = 100;
  static const int myDebug;
  static const float myDebug1 = 2.2;
  static const long scLong = 100;
  // Automatic counting works with static arrays.
  // Arrays, Non-integral and non-const statics 
  // must be initialized externally:
  static const int scInts[];
  static const long scLongs[];
  static const float scTable[];
  static const char scLetters[];
  static int size;
  static const float scFloat;
  static float table[];
  static char letters[];
};

int Values::size = 100;
const float Values::scFloat = 1.1;

const int Values::myDebug = -98;

const int Values::scInts[] = {
  99, 47, 33, 11, 7
};

const long Values::scLongs[] = {
  99, 47, 33, 11, 7
};

const float Values::scTable[] = {
  1.1, 2.2, 3.3, 4.4
};

const char Values::scLetters[] = {
  'a', 'b', 'c', 'd', 'e',
  'f', 'g', 'h', 'i', 'j'
};

float Values::table[4] = {
  1.1, 2.2, 3.3, 4.4
};

char Values::letters[10] = {
  'a', 'b', 'c', 'd', 'e',
  'f', 'g', 'h', 'i', 'j'
};


//Definition of static const class variables.
const int Values::scSize;

int main() { Values v; } ///:~

/*

With static consts of integral types you can provide an initializer inside the class, but for everything else (including arrays of integral types, even if they are static const) you must provide a single external definition for the member. These static const initializations inside classes have internal linkage, so they can be placed in header files. The syntax for initializing static arrays is the same as for any aggregate, including automatic counting.

Also note that you still MUST provide a definition for static const variables in exactly one translation unit.

*/
