#ifndef _STACKTEMPLATE_H_
#define _STACKTEMPLATE_H_ 

#include <iostream>
#include "../require.h"
using namespace std;

template <class T>
class StackTemplate
{
   int top;

   static const int size = 100;

   T Stack[size];

   public:

   StackTemplate();

   void push(const T& value );

   T pop();

   int ssize() const;

};

template <class T>
StackTemplate<T>::StackTemplate() : top(0)
{
}

template <class T>
void StackTemplate<T>::push(const T& value)
{
   require(top < size, "Too many push(es)");
   Stack[top++] = value;
}

template <class T>
T StackTemplate<T>::pop()
{
   require(top > 0, "Too many pop(s)");
   return Stack[--top];
}

template <class T>
int StackTemplate<T>::ssize() const
{
   return top;
}

#endif
