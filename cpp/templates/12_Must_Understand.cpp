/*

How to use overloaded operator[] with pointer to an object. 

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

   Array<int>* poIntArray = new Array<int>();

   int i;

   for(i = 0; i < 100; ++i)
   {
     // (*poIntArray)[i] = i * i;

      /*        OR    */

      poIntArray->operator[](i) = i * i; 
   }

   for(i = 0; i < 100; ++i)
   {
      //cout<<"(*poIntArray)["<<i<<"] = "<<(*poIntArray)[i]<<endl;
      cout<<"(*poIntArray)["<<i<<"] = "<<poIntArray->operator[](i)<<endl;
   }
   return 0;
}

/*


*/
