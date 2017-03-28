#include <iostream>
#include <boost/type_traits.hpp>
#include <boost/mpl/int.hpp>
using namespace std;
namespace mpl = boost::mpl;

int main()
{
    cout << boolalpha << boost::is_same< mpl::int_<10>::type, mpl::int_<10> >::value << endl;

    return 0;
}

