#include <iostream>
#include <cstddef>
using namespace std;

class Singleton
{
private:
   static Singleton oSingleton;

   unsigned int SingletonData;

   /* C'tor */
   Singleton(unsigned int p_data = 0) : SingletonData(p_data)
   { 
   };
   
   /* D'tor */
   virtual ~Singleton()
   { };

   /* Copy c'tor */
   Singleton(const Singleton& roSingleton)
   { };

   /* operator = */
   Singleton& operator= (const Singleton& roSingleton)
   { return *this; };

public:
   
   /* getInstance() method */
   static Singleton& getInstance() 
   { 
      return oSingleton;
   };

  /* static void removeInstance()
   {
      if(poSingleton)
      {
         delete poSingleton;
         poSingleton = NULL;
      }
   };
  */

   unsigned int getData() const
   {
      return SingletonData;
   }

   void setData(unsigned int p_data)
   {
      SingletonData = p_data;
   } 
   
}; //end of class

/* Define the static poSingleton */
Singleton Singleton::oSingleton(50);

int main()
{
Singleton& roSingleton = Singleton::getInstance();
cout<<roSingleton.getData()<<endl;
roSingleton.setData(40);
cout<<roSingleton.getData()<<endl;
Singleton& objSingleton = Singleton::getInstance();
cout<<objSingleton.getData()<<endl;
//poSingleton->removeInstance();
return 0;
}

