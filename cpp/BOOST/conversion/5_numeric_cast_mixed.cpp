/*
The most common problem is assigning a negative value to an unsigned type. The result is almost certainly not what was intended. 

Another issue is when assigning from an unsigned type to a signed type of the same size. Somehow, it seems to be easy to forget that the unsigned type can hold higher values than the signed counterpart. It's even easier to forget the types involved in an expression or function call. Here's an example that shows how these common errors are caught by numeric_cast.

*/

#include <iostream>
#include "boost/limits.hpp"
#include "boost/cast.hpp"

int main() {
  unsigned int ui=std::numeric_limits<unsigned int>::max();
  int i;

  try {
    std::cout << "Assignment from unsigned int to signed int\n";
    i=boost::numeric_cast<int>(ui);
    std::cout << i << std::endl;
  }
  catch(boost::bad_numeric_cast& e) {
    std::cout << e.what() << "\n\n";
  }

  try {
    std::cout << "Assignment from signed int to unsigned int\n";
    i=-12;
    ui=boost::numeric_cast<unsigned int>(i);
  }
  catch(boost::bad_numeric_cast& e) {
    std::cout << e.what() << "\n\n";
  }
}


