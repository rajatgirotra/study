#include <iostream>
#include <cstddef>
using namespace std;

class Singleton
{
private:
   static Singleton* poSingleton;

   unsigned int SingletonData;

   /* C'tor */
   Singleton() : SingletonData(10)
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
   static Singleton* getInstance()
   { 
      if(!poSingleton)
         poSingleton = new Singleton();
      return poSingleton;
   };

   static void removeInstance()
   {
      if(poSingleton)
      {
         delete poSingleton;
         poSingleton = NULL;
      }
   };

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
Singleton* Singleton::poSingleton = NULL;

int main()
{
Singleton* poSingleton = Singleton::getInstance();
cout<<poSingleton->getData()<<endl;
poSingleton->setData(40);
cout<<poSingleton->getData()<<endl;
poSingleton->removeInstance();
return 0;
}


   
