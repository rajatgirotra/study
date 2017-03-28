#include "5_pimpl_sample.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;

int main() try
{
   pimpl_sample ps;
   ps.do_something();

   return 0;
}catch(const int& e)
{   
   cout << "Caught exception: " << e << endl;
}
