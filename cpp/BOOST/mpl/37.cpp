// An alternate way
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
struct twice : F::template apply<
                   typename F::template apply<X>::type
               >
{
};

int main()
{
    cout << twice <f, mpl::int_<-10> >::type::value << endl;
    return 0;
}
