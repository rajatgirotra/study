/* Demonstrate a simple function object */
/* A function object is an instance of a class that overloads operator( ), the function call operator. */
/*
The Standard C++ library classifies a function object based on the number of arguments its operator( ) takes and the kind of value it returns. This classification is based on whether a function objects operator( ) takes zero, one, or two arguments:

Generator: A type of function object that takes no arguments and returns a value of an arbitrary type. A random number generator is an example of a generator. The standard library provides one generator, the function rand( ) declared in <cstdlib>, and has some algorithms, such as generate_n( ), which apply generators to a sequence.

Unary Function: A type of function object that takes a single argument of any type and returns a value that may be of a different type (which may be void).

Binary Function: A type of function object that takes two arguments of any two (possibly distinct) types and returns a value of any type (including void).

Unary Predicate: A Unary Function that returns a bool.

Binary Predicate: A Binary Function that returns a bool.

*/


#include <iostream>
using namespace std;

class get_n
{
   int value;
   
public:
   get_n(int p_arg) : value(p_arg)
   { };

   bool operator()(int n)
   {
      return (n > value);
   }
};

int main()
{
   get_n f(4);

   cout<<"f(3) = "<<std::boolalpha << f(3)<<endl; /* f(3) or f.operator()(3) */

   cout<<"f(5) = "<<f(5)<<endl;

   return 0;
}
