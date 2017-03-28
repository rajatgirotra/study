/*

templates come in two flavors: function templates and class templates. Both are wholly characterized by their parameters. Each template parameter can represent one of the following:

1.  Types (either built-in or user-defined).

2.  Compile-time constant values (for example, integers, and pointers and references to static entities; often referred to as non-type parameters).

3.  Other templates.

The examples in Volume 1 all fall into the first category and are the most common. The canonical example for simple container-like templates nowadays seems to be a Stack class. Being a container, a Stack object is not concerned with the type of object it stores; the logic of holding objects is independent of the type of objects being held. For this reason you can use a type parameter to represent the contained type:

template<class T> class Stack {
  T* data;
  size_t count;
public:
  void push(const T& t);
  // Etc.
};
 
The actual type to be used for a particular Stack instance is determined by the argument for the parameter T:

Stack<int> myStack;  // A Stack of ints
 
The compiler then provides an int-version of Stack by substituting int for T and generating the corresponding code. The name of the class instance generated from the template in this case is Stack<int>.

Non.type template parameters
A non-type template parameter must be an integral value that is known at compile time. You can make a fixed-size Stack, for instance, by specifying a non-type parameter to be used as the dimension for the underlying array, as follows.

template<class T, size_t N> class Stack {
  T data[N];  // Fixed capacity is N
  size_t count;
public:
  void push(const T& t);
  // Etc.
};
 
You must provide a compile-time constant value for the parameter N when you request an instance of this template, such as

Stack<int, 100> myFixedStack;
 
Because the value of N is known at compile time, the underlying array (data) can be placed on the runtime stack instead of on the free store. This can improve runtime performance by avoiding the overhead associated with dynamic memory allocation. Following the pattern mentioned earlier, the name of the class above is Stack<int, 100>. This means that each distinct value of N results in a unique class type. For example, Stack<int, 99> is a distinct class from Stack<int, 100>.

*/

#ifndef _URAND_H_
#define _URAND_H_ 1

#include <iostream>
#include <cassert>
#include <ctime>
#include <cstddef>
#include <cstdlib>
#include <bitset>
using namespace std;

template<unsigned int UpperBound = 10>
class Urand
{
private:
   bitset<UpperBound> used;

public:
   Urand()
   {
      srand(time(0));
   }

   unsigned int operator() ();
};

template<unsigned int UpperBound>
inline unsigned int Urand<UpperBound>::operator() ()
{
   if(used.count() == UpperBound)
      used.reset();
   unsigned int uiNewVal = 0;
   while(used[uiNewVal = (rand() % UpperBound)]); /* Until unique value is found */
   used[uiNewVal] = true;
   return uiNewVal;
}


#endif
