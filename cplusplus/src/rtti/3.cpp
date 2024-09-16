/*

You can also use dynamic_cast with references instead of pointers, but since there is no such thing as a null reference, you need another way to know if the cast fails. That other way is to catch a bad_cast exception, as follows:

*/


//: C08:CatchBadCast.cpp
#include <typeinfo>
#include "Security.h"
using namespace std;
 
int main() {
  Metal m;
  Security& s = m;
  try {
    Investment& c = dynamic_cast<Investment&>(s);
    cout << "It's an Investment" << endl;
  } catch(bad_cast&) {
    cout << "s is not an Investment type" << endl;
  }
  try {
    Bond& b = dynamic_cast<Bond&>(s);
    cout << "It's a Bond" << endl;
  } catch(bad_cast&) {
    cout << "It's not a Bond type" << endl;
  }
} ///:~

/*
The bad_cast class is defined in the <typeinfo> header, and, like most of the standard library, is declared in the std namespace.
*/
