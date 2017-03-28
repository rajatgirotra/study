#include <iostream>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <typeinfo>

namespace mpl = boost::mpl;
using namespace std;

int main()
{
    typedef mpl::integral_c<int, 10> ic10;
    typedef mpl::int_<10> i10;

    cout << "Integral C details" << endl;
    cout << "integral_c<int, 10>::value  =  " << ic10::value << endl;
    cout << "integral_c<int, 10>::value_type  =  " << typeid(ic10::value_type).name() << endl;

    cout << "\n\n\nInt_ details" << endl;
    cout << "int_<10>::value  =  " << i10::value << endl;
    cout << "int_<10>::value_type  =  " << typeid(i10::value_type).name() << endl;

    // BOOST_MPL_ASSERT (( boost::is_same<ic10::type, i10::type> ));
    return 0;
}
