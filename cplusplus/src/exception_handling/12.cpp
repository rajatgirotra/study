/* Function Level Try blocks 

Since constructors can routinely throw exceptions, you might want to handle exceptions that occur when an objects member or base subobjects are initialized. To do this, you can place the initialization of such subobjects in a function-level try block. In a departure from the usual syntax, the try block for constructor initializers is the constructor body, and the associated catch block follows the body of the constructor, as in the following example:

*/



#include <iostream>
#include <exception>
using namespace std;

class Foo
{
   private:
      int i;

   public:
      Foo(int i = 0) : i(i)
   { cout<<"Foo::Foo(int i = 0)"<<endl;
      throw FooExcept();
   };

      class FooExcept
      {
      };

      ~Foo()
      { cout<<"Foo::~Foo()"<<endl; 
      }

      Foo(const Foo& roFoo) : i(roFoo.i)
   { cout<<"Foo::Foo(const Foo& roFoo)"<<endl;
   }
};

class Bar : public Foo
{
   public:

      Bar(int i) try : Foo(i)
      { cout<<"Bar::Bar(int)"<<endl;
      } catch(Foo::FooExcept& roFooExcept)
      {
         cout<<"Exception Caught..!! Rethrowing it"<<endl;
         throw BarExcept(" Something has happened");
      }

      class BarExcept
      {
         const char* msg;

         public:

         BarExcept(const char* msg) : msg(msg)
         {  cout<<"BarExcept::BarExcept(const char*)"<<endl; }

         const char* what() const
         {
            return msg;
         }
      };
};

int main()
{
   try
   {
      Bar oBar(3);
   }
   catch(Bar::BarExcept& roBarExcept)
   {
      cout<<"Exception Caught in BarExcept"<<roBarExcept.what()<<endl;
   }
   return 0;
}


/*

Notice that the initializer list in the constructor for Derived goes after the try keyword but before the constructor body. If an exception does occur, the contained object is not constructed, so it makes no sense to return to the code that created it. For this reason, the only sensible thing to do is to throw an exception in the function-level catch clause.

Although it is not terribly useful, C++ also allows function-level try blocks for any function

*/
