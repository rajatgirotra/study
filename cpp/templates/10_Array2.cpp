/*
Non inline member function templates
 */

#include <iostream>
#include "../require.h"
using namespace std;

template <class T>
class Array
{
   static const int size = 100;
   T arr[size];

   public:

   T& operator[](int p_index);
};

template <class T>
T& Array<T>::operator[] (int p_index)
{
   require(p_index >= 0 && p_index < size, "Index out of bounds");
   return arr[p_index];
}

int main()
{

   Array<int> oIntArray;
   Array<float> oFloatArray;

   int i;

   for(i = 0; i < 10; ++i)
   {
      oIntArray[i] = i * i;
      oFloatArray[i] = (float)i * 1.414;
   }

   for(i = 0; i < 10; ++i)
   {
      cout<<"oIntArray["<<i<<"] = "<<oIntArray[i]<<"    oFloatArray["<<i<<"] = "<<oFloatArray[i]<<endl;
   }
   return 0;
}

/*

Any reference to a template's class name must be accompanied by its template argument list, as in Array<T>::operator[].
You can imagine that internally, the class name is being decorated with the arguments in the template argument list to produce
a unique class name identifier for each template instantiation.

*/
