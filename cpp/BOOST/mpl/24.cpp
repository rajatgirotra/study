#include <iostream>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
using namespace std;

namespace mpl = boost::mpl;

template <typename T1, typename T2>
struct plus_f : mpl::plus <T1, T2>
{}; //Metafunction forwarding, very simple

int main()
{
    //plus_f::type will be same as mpl::plus <T1, T2>::type
    cout << plus_f < mpl::int_<10>, mpl::int_<5> >::type::value << endl;
    return 0;
}
