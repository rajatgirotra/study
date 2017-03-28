/*
 * By now, you know a metafunction is function which has a nested ::type member. Let us look at some of the boost mpl
 * metafunctions.
 */

/* Metafunction "identity"
 * template <typename T>
 * struct identity
 * {
 *     typedef T type;
 * };
 */

#include <iostream>
#include <string>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
using namespace std;

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::identity<int>::type intMplType;
    typedef mpl::identity<const int>::type constIntMplType;
    typedef int intType;

    cout << boolalpha << boost::is_same< intMplType, intType>::value << endl;
    cout << boolalpha << boost::is_same< constIntMplType, intType>::value << endl;

    return 0;
}
