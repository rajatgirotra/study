/* Understand bind2nd(). */
/* Understand this piece of code */

/*

template<typename Operation, typename T>
binder2nd<Operation> bind2nd(const Operation& op, const T& x)
{
   return binder2nd<Operation> (op, typename Operation::second_argument_type(x));
}

template <class Operation> class binder2nd
  : public unary_function <typename Operation::first_argument_type,
                           typename Operation::result_type>
{
protected:
  Operation op;
  typename Operation::second_argument_type value;
public:
  binder2nd ( const Operation& x,
              const typename Operation::first_argument_type& y) : op (x), value(y) {}
  typename Operation::result_type
    operator() (const typename Operation::first_argument_type& x) const
    { return op(x,value); }
};

*/

#include <iostream>
#include <cstddef>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

int main()
{
   int myInts[] = { 10, 20, 30, 13, 15, 16 };

   remove_copy_if(myInts, myInts + sizeof(myInts)/sizeof(myInts[0]), ostream_iterator<int>(cout, "\n"), bind2nd(greater<int>(), 15));

   return 0;
}

