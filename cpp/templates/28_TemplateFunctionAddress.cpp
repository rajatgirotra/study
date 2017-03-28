#include <iostream>

using namespace std;

template <typename T>
void foo(T* poT)
{
   cout<<"Foo Called with "<<*poT<<endl;
}

void h(void (*poFunc)(int* ))
{
   cout<<"h Called"<<endl;
   int* poInt = new int(10);
   (*poFunc)(poInt);
   delete poInt;
}

template <typename T>
void g(void (*poFunc)(T* poT))
{
   cout<<"g called"<<endl;
}

int main()
{
   h(&foo<int>);  /* Full specification */
   h(&foo);   /* Compiler Deduces type itself */

   g<int>(&(foo<int>)); /* Full specification */
   g(&(foo<int>)); /* Compiler deduces */
   g<int>(&(foo)); /* this also works */

   return 0;
}

