#include <iostream>
using namespace std;

class A 
{ 
public:
  virtual void test()
  {
    cout<<"A::test()"<<endl;
  };
};

void consumer(A* poA)
{
poA->test();
}
   

class B : private A
{
private:
   void test()
   {
      cout<<"B::test()"<<endl;
   };

public:
   void use()
   {
      consumer(this); 
   } // that's what you can do!

   B() 
   { }
};

int main()
{
   B b;
   b.use(); 

//   consumer(new B());

   return 0;
}

/*

No, breaking would mean that you've closed something already. That's not
the case -- you cannot protect B::test() if there is already a public
alias to it (A::test()). There are situations however where protecting
B::test() would make sense:

- You inherit from A in a non-public way, because you don't want someone
to use B directly: 
- You mark B::test private, because B should only be used
polymorphically (i.e. you want to forbid b.B::test(), because this may
not work if B is a subclass) 

*/
