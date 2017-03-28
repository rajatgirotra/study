#include <iostream>
#include <fstream>
using namespace std;

ofstream out("ByteTest.out");

class Byte
{
unsigned char b;

public:

   Byte(unsigned char bb = 0) : b(bb)
   {
      cout<<"Byte::Byte(unsigned char bb = 0)"<<endl; 
   }

   /* Overload - operator as a friend function */
   Byte operator - (const Byte& x) 
   {
     cout<<"Byte operator - (const Byte& x)"<<endl;
     return Byte(b - x.b);

   }
  
   #if 1
   Byte& operator |= (const Byte& x)
   {
      cout<<"Byte& operator != (const Byte& x)"<<endl;
      b |= x.b; 
      return *this;
   }

   bool operator < (const Byte& x)
   {
     cout<<"bool operator < (const Byte& x)"<<endl;
     return ((b < x.b) ? true : false);
   } 
 
   const Byte& operator = (const Byte& x)
   {
      cout<<"const Byte& operator = (const Byte& x)"<<endl; 
      b = x.b;
      return *this;
   }
   #endif

   unsigned char getData() { return b; };

   void print(ofstream& os) const
   {
       os << "0x" << std::hex << int(b) << std::dec;
   };
};

class Byte2 : public Byte
{
public:
  Byte2(unsigned char bb = 0) : Byte(bb)
  { };

};

int main()
{
#if 1
Byte2 b1(9), b2(47);

Byte2 b3;
(b1-b2).print(out);
 
cout<<b3.getData()<<endl; 
#endif
return 0;
}
