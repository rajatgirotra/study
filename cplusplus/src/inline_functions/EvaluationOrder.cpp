/*

Forward references
If you're imagining what the compiler is doing to implement inlines, you can confuse yourself into thinking there are more limitations than actually exist.
 In particular, if an inline makes a forward reference to a function that hasn't yet been declared in the class (whether that function is inline or not), it can seem like the compiler won't be able to handle it.
*/


//: C09:EvaluationOrder.cpp
// Inline evaluation order
#include <iostream>
using namespace std;

namespace {
  const int i = 100;
}

class Forward {
  int i;
public:
  Forward() : i(0) {}
  // Call to undeclared function:
  int f() const { return g() + 1; };
  int g() const { return ::i; };
};


int main() {
  Forward frwd;
  cout << frwd.f() << endl;
} ///:~

/*


In f(), a call is made to g( ), although g( ) has not yet been declared. This works because the language definition states that no inline functions in a class shall be evaluated until the closing brace
 of the class declaration.
*/



