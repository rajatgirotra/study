/*
unexpected() - If an exception throws an exception not specified in its exception exception, the compiler calls the unexpected() function whose default behavior is to call
terminate() to terminate the execution. However, if you specify std::bad_exception in the exception specification, the compiler calls unexpected which then rethrows the std::bad_exception.
*/

// set_unexpected example
#include <iostream>
#include <exception>

class E1
{};

class E2
{};

void myunexpected()
{
  std::cout << "unexpected called\n";
  throw;      // throws int (in exception-specification)
}

void f() throw (E1, std::bad_exception) 
{
   //throw E1();

   throw E2();
}

int main (void) try 
{
  std::set_unexpected (myunexpected);
  f();
}catch (E1&) { 
  std::cerr << "caught exception E1\n";
 }catch (std::bad_exception& e) { 
    std::cerr << "caught exception "<<e.what()<<std::endl; 
  }


