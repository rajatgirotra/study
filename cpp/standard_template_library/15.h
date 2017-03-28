/* How to write your own algorithms */
#ifndef _PRINT_H_
#define _PRINT_H_

#include <iostream>

template <typename T>
inline void PRINT_ELEMENTS (const T& coll, const char* optstr = " ")
{
   std::cout<<optstr<<std::endl;
   
   for(auto constIter = coll.cbegin(); constIter != coll.cend(); ++constIter)
      std::cout<<*constIter<<' ';

   std::cout<<std::endl;
}

#endif
