// Before you go to 20.cpp, we'll show another metafunction plus in the mpl library.
#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace std;
namespace mpl = boost::mpl;

int main()
{
    cout << mpl::plus < mpl::int_<10>, mpl::int_<20> >::value << endl;
    BOOST_MPL_ASSERT (( boost::is_same<mpl::plus < mpl::int_<10>, mpl::int_<20> >::type, mpl::integral_c<int, 30>::type > ));
    BOOST_MPL_ASSERT (( boost::is_same<mpl::plus < mpl::int_<10>, mpl::int_<20> >::type, mpl::int_<30>::type > ));
    return 0;
}

/*
 * The template parmeters for plus must be integral constant types.
 * Also the type typedef is of type integral_c<>. That is why we get in assert in second
 * BOOST_MPL_ASSERT(), not the first one.
 */
