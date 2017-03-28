#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

/* Usage:
   mpl::eval_if<C, f1, f2>
   C is a type. if C::value == true, then 
    mpl::eval_if<>::type is same as f1, else
    mpl::eval_if<>::type is same as f2
*/

int main() {
    return 0;
}
