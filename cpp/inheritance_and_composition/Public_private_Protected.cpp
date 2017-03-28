#include <iostream>
#include <cstdlib>
using namespace std;

class Base
{
private:
   int privateBaseData;
   void privateBase()
   {
      cout<<"Private Base"<<endl; 
   }

public:
   int publicBaseData;
   void publicBase()
   {
      cout<<"Public Base"<<endl;
   }

protected:
   int protectedBaseData;
   void protectedBase()
   {
      cout<<"Protected Base"<<endl;
   }
};

class Derv : protected Base
{
private:

   int privateDervData;
   void privateDerv()
   {
      cout<<"Private Derived"<<endl;
   }

public:
   int publicDervData;
   void publicDerv()
   {
      cout<<"Public Derived"<<endl;
   }

protected:
   int protectedDervData;
   void protectedDerv()
   {
      cout<<"Protected Derived"<<endl;
   }
};

int main()
{
cout<<"Size of Base = "<<sizeof(Base)<<endl; 
cout<<"Size of Derv = "<<sizeof(Derv)<<endl; 

Base objBase;
Derv objDerv;

/* Access private members. Related to point 1 */
#if 0
objDerv.privateBaseData = 10;
objDerv.privateDervData = 20;
objDerv.privateBase();
objDerv.privateDerv();
#endif

/* Access public members. Relates to point 2 */
#if 0
objDerv.publicBaseData = 10;
objDerv.publicDervData = 20;
objDerv.publicBase();
objDerv.publicDerv();
#endif

/* Access protected members. Relates to point 3 */
#if 0
objDerv.protectedBaseData = 10;
objDerv.protectedDervData = 20;
objDerv.protectedBase();
objDerv.protectedDerv();
#endif


/* Access private members. Related to point 4 */
#if 1
objDerv.privateBaseData = 10;
objDerv.privateDervData = 20;
objDerv.privateBase();
objDerv.privateDerv();
#endif

return 0;
}

/* 

When a class is inherited publicly:

1] All the private member functions and member data in Base class become private in Derived class. They can not be accessed in main. Also they can not be accessed in member functions of the derived class. They can only be accessed by member functions of the base class.

2] All the public member functions and member data in the Base class become public in the Derived class. They can be accessed in main. Also they can be accessed by all member functions in the derived class. 

3] All the  protected member functions and member data in the Base class become protected in the Derived class. They cannot be accessed in main; but can be accessed anywhere in the Derived class. (Still to see if they can be accessed by a next level of subclass. 


When a class is inherited privately 
1] All the private member functions and member data in Base class become private in Derived class. They can not be accessed in main. Also they can not be accessed in member functions of the derived class. They can only be accessed by member functions of the base class.

2] All the public member functions and member data in the Base class become private in the Derived class. They cannot be accessed in main. But they can be accessed by all member functions in the derived class. 

3] All the  protected member functions and member data in the Base class become protected in the Derived class. They cannot be accessed in main; but can be accessed anywhere in the Derived class. (Still to see if they can be accessed by a next level of subclass. 
*/

