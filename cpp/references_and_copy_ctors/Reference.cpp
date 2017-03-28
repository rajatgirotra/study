/*

The most common place youll see references is as function arguments and return values. When a reference is used as a function argument, any modification to the reference inside the function will cause changes to the argument outside the function. Of course, you could do the same thing by passing a pointer, but a reference has much cleaner syntax. (You can think of a reference as nothing more than a syntax convenience, if you want.)

If you return a reference from a function, you must take the same care as if you return a pointer from a function. Whatever the reference is connected to shouldnt go away when the function returns, otherwise youll be referring to unknown memory.

Heres an example:

*/


//: C11:Reference.cpp
// Simple C++ references

#include <iostream>
using namespace std;

int* f(int* x) 
{
  (*x)++;
  return x; // Safe, x is outside this scope
}

int& g(int& x) 
{
  x++; // Same effect as in f()
  return x; // Safe, outside this scope
}

int& h() 
{
  int q;
//return q;  // Error
  static int x = -79;
  return x; // Safe, x lives outside this scope
}

int main() 
{
  int a = 0;
  int *poRet = f(&a); // Ugly (but explicit)
  cout<<"f(&a) = "<<*poRet<<endl;
   
  a = -34;
  int& b = g(a);  // Clean (but hidden)
  cout<<"g(a) = "<<b<<endl;

  int &c = h();
  cout<<"h() = "<<c<<endl;
  return 0;
} ///:~


