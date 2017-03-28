#include <iostream>
#include <string>
using namespace std;

template <class T>
const T& max_(const T& a, const T& b)
{
if ( a > b )
   return a;
else
   return b;
}

class Integer
{
int iDataValue;

public:
   Integer(int p_Data = 0) : iDataValue(p_Data)
   { };

   //friend bool operator > (const Integer& roInteger1, const Integer& roInteger2);

   #if 1
   bool operator > (const Integer& roInteger) const
   {
      return (iDataValue > roInteger.iDataValue);
   }
   #endif

   int getData() const
   {
      return iDataValue;
   };
};

#if 0
bool operator > (const Integer& roInteger1, const Integer& roInteger2)
{
   if(roInteger1.iDataValue > roInteger2.iDataValue)
      return true;
   else
      return false;
}
#endif

int main()
{
   int a = 5,
       b = 10;

   Integer obj_1(-23);
   Integer obj_2(-78);

   cout<<max_(a, b)<<endl;

   cout<<(max_(obj_1, obj_2)).getData()<<endl;
   
   return 0;
}
