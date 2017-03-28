/*

   The Derived3 class in NameHidin2.cpp suggests that you cannot modify the return type of a virtual function during overriding. This is generally true, but there is a special case in which you can slightly modify the return type. If youre returning a pointer or a reference to a base class, then the overridden version of the function may return a pointer or reference to a class derived from what the base returns. For example:

 */

#include <iostream>

using namespace std;

class PetFood
{
   public:
      virtual string foodType() const = 0;
};

class Pet
{
   public:
      virtual string type() const = 0;
      virtual PetFood* eats()  = 0;
};

class Bird : public Pet
{
   public:
      string type() const
      {
         return "Birds"; 
      }

      PetFood* eats()
      {
         return &bf;
      }

      class BirdFood : public PetFood
   {
      public:
         string foodType() const
         { 
            return "Bird Food";
         }

   };

   private:
      BirdFood bf;
};

class Cat : public Pet
{

   public:
      string type() const
      {
         return "Cats";
      }



      class CatFood : public PetFood
   {
      public:
         string foodType() const
         {
            return "Birds";
         }
   };

      CatFood* eats()
      {
         return &cf;
      }

   private:
      CatFood cf;
};

int main()
{
   Bird b;
   Cat c;
   Pet* p[] = { &b, &c };
   int i;
   for(i = 0; i < (sizeof(p)/sizeof(*p)); ++i)
   {
      cout<<p[i]->type()<<" eat ";
      cout<<p[i]->eats()->foodType();
      cout<<endl;
   }

   Cat::CatFood* cf = c.eats(); 
 
   /* Error; Cannot downcast automatically; should do it explicitely */ 
   //Bird::BirdFood* bf = b.eats();

   /* Like this */
   Bird::BirdFood* bf = dynamic_cast<Bird::BirdFood*>(b.eats());
   if(!bf)
   {
      cout<<"Bird Food is NULL"<<endl;
   }
   else
   {
      cout<<"Bird Food is NOT NULL"<<endl;
   }
   return 0;
}



