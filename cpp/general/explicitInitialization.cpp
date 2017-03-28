/*
Explicit Initialization for Fundamental TypeS
If you use the syntax of an explicit constructor call without arguments, fundamental types are
initialized with zero:

int i1; // undefined value
int i2 = int(); // initialized with zero

This feature is provided to enable you to write template code that ensures that values of any type
have a certain default value. For example, in the following function the initialization guarantees
that x is initialized with zero for fundamental types:
*/

#include <iostream>
using namespace std;

template <typename T>
void f(T x = T())
{
   cout<<"x = "<<x<<endl;
}

int main()
{
   f<int>();
   f<double>();
   f<long>();
   f<float>();
   f<short>();
   f<bool>();
   
   return 0;
}
