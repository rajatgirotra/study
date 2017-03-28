/*

   The template keyword tells the compiler that the class definition that follows will manipulate one or more unspecified types. At the time the actual class code is generated from the template, those types must be specified so that the compiler can substitute them.

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

   T& operator[](int p_index)
   {
      require(p_index >= 0 && p_index < size, "Index out of bounds");
      return arr[p_index];
   }

};

int main()
{

   Array<int> oIntArray;
   Array<float> oFloatArray;

   int i;

   for(i = 0; i < 20; ++i)
   {
      oIntArray[i] = i * i;
      oFloatArray[i] = (float)i * 1.414;
   }

   for(i = 0; i < 20; ++i)
   {
      cout<<"oIntArray["<<i<<"] = "<<oIntArray[i]<<"    oFloatArray["<<i<<"] = "<<oFloatArray[i]<<endl;
   }
   return 0;
}

/*

You can see that it looks like a normal class except for the line

    template<class T> 

which says that T is the substitution parameter, and that it represents a type name. Also, you see T used everywhere in the class where you would normally see the specific type the container holds.

In main( ), you can see how easy it is to create Arrays that hold different types of objects. When you say

    Array<int> ia;
    Array<float> fa;

the compiler expands the Array template (this is called instantiation) twice, to create two new generated classes, which you can think of as Array_int and Array_float. (Different compilers may decorate the names in different ways.) These are classes just like the ones you would have produced if you had performed the substitution by hand, except that the compiler creates them for you as you define the objects ia and fa. Also note that duplicate class definitions are either avoided by the compiler or merged by the linker.

*/
