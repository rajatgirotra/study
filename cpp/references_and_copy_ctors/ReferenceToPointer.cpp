/*

Pointer references

In C, if you want to modify the contents of the pointer rather than what it points to, your function declaration looks like: 

void f(int**);
and youd have to take the address of the pointer when passing it in:


int i = 47;
int* ip = &i;
f(&ip); 
With references in C++, the syntax is cleaner. The function argument becomes a reference to a pointer, and you no longer have to take the address of that pointer. Thus,

*/

//: C11:ReferenceToPointer.cpp
#include <iostream>
using namespace std;

void increment(int*& i) { i++; }

int main() {
  int* i = 0;
  cout << "i = " << i << endl;
  increment(i);
  cout << "i = " << i << endl;
} ///:~

