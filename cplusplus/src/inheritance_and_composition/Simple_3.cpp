#include <iostream>
using namespace std;

class Base
{
   private:
      int BaseData;

   public:
      Base() 
      {
         cout<<"Base::Base()"<<endl;
      };

      Base(const Base&)
      {
         cout<<"Base::Base(const Base& roBase)"<<endl;
      };

      Base& operator = (const Base&)
      {
         cout<<"Base::Base& operator = (const Base& roBase)"<<endl;
         return *this;
      }

      ~Base()
      {
         cout<<"Base::~Base()"<<endl;
      } 
};

class Derv
{
   private:
      Base oBase; //Composition
      int DervData;

   public:
      Derv()
      {
         cout<<"Derv::Derv()"<<endl;
      }

      Derv(const Derv& oDerv) : oBase(oDerv.oBase)
      {
         cout<<"Derv::Derv(const Derv& roDerv)"<<endl;
      }

      Derv& operator= (const Derv&)
      {
         cout<<"Derv::Derv& operator= (const Derv& roDerv)"<<endl;
         return *this;
      }
   
      ~Derv()
      {
         cout<<"Derv::~Derv()"<<endl;
      }
};

class Derv2 : public Derv
{

   private:
      int Derv2Data;

   public:
      Derv2()
      {
         cout<<"Derv2::Derv2()"<<endl;
      }

      Derv2(const Derv2& roDerv2) : Derv(roDerv2)
      {
         cout<<"Derv2::Derv2(const Derv2& roDerv2)"<<endl;
      }

      Derv2& operator= (const Derv2&)
      {
         cout<<"Derv2::Derv2& operator=(const Derv2& roDerv2)"<<endl;
         return *this;
      } 
 
      ~Derv2()
      {
         cout<<"Derv2::~Derv2()"<<endl;
      }
};


int main()
{
   Derv2 oDerv2_1;
   cout<<endl;
   Derv2 oDerv2_2(oDerv2_1); 
   cout<<endl;
   return 0;
}

