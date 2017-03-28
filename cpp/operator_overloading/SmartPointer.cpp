/*

The operator -> is generally used when you want to make an object appear to be a pointer. Since such an object has more smarts built into it than exist for a typical pointer, an object like this is often called a smart pointer. These are especially useful if you want to wrap a class around a pointer to make that pointer safe, or in the common usage of an iterator, which is an object that moves through a collection /container of other objects and selects them one at a time, without providing direct access to the implementation of the container.

*/



#include <iostream>
#include <vector>
using namespace std;

class Object
{
   static int i, j;

   public:

   void f() { cout<<i++<<endl; }
   void g() { cout<<j++<<endl; }
};

int Object::i = 47;
int Object::j = 129;

class ObjectContainer
{
   vector<Object*> a;

   public:

   void add(Object* poObject)
   {
      a.push_back(poObject);
   }
   friend class SmartPointer;
};

class SmartPointer
{
   ObjectContainer& m_ObjectContainer;
   int index;

   public:
   SmartPointer(ObjectContainer& roObjectContainer) : m_ObjectContainer(roObjectContainer)
   { index = 0; };

   bool operator++()
   {
      if (index >= m_ObjectContainer.a.size())
         return false;

      if(m_ObjectContainer.a[++index] == 0) return false;
      return true;
   }

   bool operator++ (int)
   {
      return operator++();
   }


   Object* operator-> () const
   {
      return m_ObjectContainer.a[index];
   } 

};

int main()
{
   Object objObject[10];

   ObjectContainer objOC;

   for(int i=0; i < 10; ++i)
   {
      objOC.add(&objObject[i]);
   }

   SmartPointer sp(objOC);

   do
   {
      sp->f();
      sp->g();
   }while (sp++);

}

