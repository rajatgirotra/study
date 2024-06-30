#include <iostream>
using namespace std;

class Base
{
   public:
      int BaseData;

   public:
      Base() : BaseData(10)
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
      Derv() : DervData(20)
      {
         cout<<"Derv::Derv()"<<endl;
      }

      Derv(const Derv& oDerv) : oBase(oDerv.oBase)
      {
         cout<<"Derv::Derv(const Derv& roDerv)"<<endl;
      }

      Derv& operator= (const Derv& roDerv)
      {
         /* This is the explicit call */
         oBase = roDerv.oBase;

         cout<<"Derv::Derv& operator= (const Derv& roDerv)"<<endl;
         return *this;
      }
   
      ~Derv()
      {
         cout<<"Derv::~Derv()"<<endl;
      }
  
      int getBaseData() const
      {
         return this->oBase.BaseData; 
      }
};

class Derv2 : public Derv
{

   private:
      int Derv2Data;

   public:
      Derv2() : Derv2Data(30)
      {
         cout<<"Derv2::Derv2()"<<endl;
      }

      Derv2(const Derv2& roDerv2) : Derv(roDerv2)
      {
         cout<<"Derv2::Derv2(const Derv2& roDerv2)"<<endl;
      }

      Derv2& operator= (const Derv2& roDerv2)
      {
         /* This is the explicit call */
         Derv::operator=(roDerv2);

         cout<<"Derv2::Derv2& operator=(const Derv2& roDerv2)"<<endl;
         return *this;
      } 
 
      ~Derv2()
      {
         cout<<"Derv2::~Derv2()"<<endl;
      }
     
      void display() const
      {
          cout<<"BaseData = "<<getBaseData()<<endl;
      };
};


int main()
{
   Derv2 oDerv2_1;
   cout<<endl;

   oDerv2_1.display();
   Derv2 oDerv2_2(oDerv2_1); 
   cout<<endl;
   #if 1
   oDerv2_1 = oDerv2_2;  /* Concentrate on output of this line */
   cout<<endl;
   #endif
   return 0;
}

/* The assignment operator will not call any of the base class versions unless you explicitly call it */
/* You can uncomment the explicit calls and see the output for urself */
