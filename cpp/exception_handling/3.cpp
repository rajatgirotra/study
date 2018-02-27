/* In this program, first the c'tor is called to create an object oA; then the throw call creates a copy of the object oA; so the copy c'tor
   is called; then that object is thrown into the catch block where the copy c'tor is called again to create the object objA. At the end of the catch
   block, both the nameless temporary object which was thrown and the object objA is destroyed. */


#include <iostream>
using namespace std;

class A
{
  private:
    const char* const data;

    static int i;
    int object_number;

  public:
    A(const char* const msg) : data(msg), object_number(0)
    { 
       object_number = ++i;
       cout<<"A::A(const char* const) object_number = "<<i<<"   data = "<<data<<endl; 
    }

    ~A()
    {
      cout<<"A::~A() : Destroying object = "<<object_number<<"   data = "<<data<<endl; 
    }

    A(const A& roA) : data("Copy of something has happened"), object_number(0)
    {
      object_number = ++i;
      cout<<"A::A(const A&) object number =  "<<i<<endl;
    }

    void displayData()
    { cout<<data; }
};

int A::i = 0;

void foo()
{
  throw A("something has happened");
}

int main()
{
  try
  {
    cout<<"Inside try block: before the error generating instruction"<<endl;
    foo();
    cout<<"Inside try: after the error generating instruction"<<endl;
  }
  //catch(A& objA)
  catch(A objA)
  {
    cout<<"Inside the catch block: Exception Caught ";
    objA.displayData();
    cout<<endl;
  }
  cout<<"After the catch block just before ending main"<<endl;

  return 0;
}

