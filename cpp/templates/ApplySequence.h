#include <iostream>

template <typename Seq, typename T, typename R, typename A>
R apply(Seq& seq, R (T::*funcPtr)(A), A arg)
{
   typename Seq::iterator iter = seq.begin();
   while (iter != seq.end())
   {
      (*iter->*funcPtr)(arg);
      ++iter;
   }
}


