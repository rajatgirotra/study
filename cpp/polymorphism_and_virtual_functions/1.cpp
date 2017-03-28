/* How do you define a copy constructor or an overloaded = operator for a class that contains a pointer to an ABC */

#include <iostream>
#include <cassert>
using namespace std;

class AbstractBase
{
public:
  
   virtual void display() = 0;

   virtual AbstractBase* clone() = 0;

   virtual ~AbstractBase()
   { cout<<"AbstractBase d'tor running"<<endl; } ;
};

class Derv1 : public AbstractBase
{
public:
   
    void display()
    {
       cout<<"Derv1::display()"<<endl;
    };

    Derv1* clone()
    {
       return new Derv1(*this);
    }
 
    ~Derv1()
    { cout<<"Derv1 d'tor running"<<endl; } ;
    
};

class Derv2 : public AbstractBase
{
public:

   void display()
   {
     cout<<"Derv2::display()"<<endl;
   }

   Derv2* clone()
   {
      return new Derv2(*this);
   }

   ~Derv2()
   { cout<<"Derv2 d'tor running"<<endl; } ;
};

class ABCContainer
{
private:

    AbstractBase* poAbstractBase;

public:

    ABCContainer(AbstractBase* p_AbstractBase) : poAbstractBase(p_AbstractBase)
    {
        assert(p_AbstractBase != NULL);
    }

    ~ABCContainer()
    {
       poAbstractBase = NULL;
    }

    ABCContainer(const ABCContainer& roABCContainer)
    {
       poAbstractBase = roABCContainer.poAbstractBase->clone();
    }

    ABCContainer& operator = (const ABCContainer& roABCContainer)
    {
       if(this != &roABCContainer)
       {
          AbstractBase* poABase = roABCContainer.poAbstractBase->clone();
          delete poAbstractBase;
          poAbstractBase = poABase;
       }
       return *this;
   }
  
   void call()
   {
      poAbstractBase->display();
   }
};
       

    
  /* Refer to abcs.html in c++ faq lite */ 

int main()
{
   AbstractBase* poDerv1 = new Derv1();
   AbstractBase* poDerv2 = new Derv2();
   
   ABCContainer obj1(poDerv1);
   ABCContainer obj2(poDerv2);

   obj1.call(); 
   obj2.call(); 

   ABCContainer obj3(obj2);
   obj3.call();
  
   obj3 = obj1;
   obj3.call();

   cout<<"Starting to destroy"<<endl;
   delete poDerv2;
   delete poDerv1;

   return 0;
}
