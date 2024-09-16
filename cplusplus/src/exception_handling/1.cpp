/* If an exception is unhandled as in this case, the d'tor for the class doesn't execute, and the programs aborts after throwing the exception */

#include <iostream>
using namespace std;

class A
{

const char* const data;
public:
   A(const char* const msg) : data(msg)
   { cout<<"A::A(const char* const)"<<endl; }

   ~A()
   {
      cout<<"A::~A()"<<endl; 
   }

   A(const A& roA) : data(roA.data)
   {
      cout<<"A::A(const A&)"<<endl;
   }
};

void foo()
{
throw A("something has happened");
}

int main()
{
cout<<"Inside Main: before the error generating instruction"<<endl;
foo();
cout<<"Inside main: after the error generating instruction"<<endl;
return 0;
}

