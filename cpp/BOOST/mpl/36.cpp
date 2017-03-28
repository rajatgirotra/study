// High order metafunctions - A metafunction that operates on another metafunction.
// Example, let say you have a unary metafunction class f which operates on some data X, 
// write a high order meta function that does f(x) twice,
//
// so new metafunction = f(f(x))
//
#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/negate.hpp>
using namespace std;
namespace mpl = boost::mpl;

struct f
{
    template <typename X>
    struct apply : mpl::negate<X>
    {};
};


template <typename F, typename X>
struct twice
{
    typedef typename F::template apply<X>::type once;
    typedef typename F::template apply<once>::type type;
};

int main()
{
    cout << twice <f, mpl::int_<-10> >::type::value << endl;
    return 0;
}
