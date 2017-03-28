/*

Using the Singleton design pattern, create a class that can have maximum of two objects */ 

#include <iostream>
#include <cstddef>
using namespace std;

class Singleton
{
private:
   static Singleton* poSingleton[2];
   static unsigned int uiCount;
   static const unsigned int MAX_OBJECTS = 2;

   unsigned int SingletonData;

   /* C'tor */
   Singleton() : SingletonData(10)
   { 
      ++uiCount;
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
   static Singleton* getInstance(unsigned int count)
   { 
      if(count >= MAX_OBJECTS) 
         return NULL;
      if(!poSingleton[count])
      {
         poSingleton[count] = new Singleton();
         ++uiCount;
      }
      return poSingleton[count];
   };

   static void removeInstance(unsigned int count)
   {
      if(count >= MAX_OBJECTS) return;
      if(poSingleton[count])
      {
         delete poSingleton[count];
         poSingleton[count] = NULL;
         --uiCount;
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
Singleton* Singleton::poSingleton[2] = { NULL };
unsigned int Singleton::uiCount = 0;

int main()
{
Singleton* poSingleton_1 = Singleton::getInstance(0);
cout<<poSingleton_1->getData()<<endl;
poSingleton_1->setData(40);
cout<<poSingleton_1->getData()<<endl;

Singleton* poSingleton_2 = Singleton::getInstance(1);
cout<<poSingleton_2->getData()<<endl;
poSingleton_2->setData(50);
cout<<poSingleton_2->getData()<<endl;

poSingleton_1->removeInstance(1);
poSingleton_2->removeInstance(0);
return 0;
}


   
