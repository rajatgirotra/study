/*
You need a copy-constructor only if you're going to pass an object of your class by value. If that never happens, you don't need a copy-constructor.

Preventing pass-by-value
But you say, if I don't make a copy-constructor, the compiler will create one for me. So how do I know that an object will never be passed by value?.

There's a simple technique for preventing pass-by-value: declare a private copy-constructor. You don't even need to create a definition, unless one of your member functions or a friend function needs to perform a pass-by-value. If the user tries to pass or return the object by value, the compiler will produce an error message because the copy-constructor is private. It can no longer create a default copy-constructor because you.ve explicitly stated that you.re taking over that job.

Here.s an example:

*/

//: C11:NoCopyConstruction.cpp
// Preventing copy-construction
#include <iostream>
using namespace std;

class NoCC {
  int i;
  NoCC(const NoCC&); // No definition
public:
  NoCC(int ii = 0) : i(ii) {}
};

NoCC::NoCC(const NoCC& oNoCC)
{
   cout<<"Private Copy C'tor"<<endl;
}

void f(NoCC);

int main() {
  NoCC n;
//! f(n); // Error: copy-constructor called
//! NoCC n2 = n; // Error: c-c called
//! NoCC n3(n); // Error: c-c called
  return 0;
} ///:~

