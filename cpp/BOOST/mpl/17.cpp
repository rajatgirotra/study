/*
 * Integral Constants. MPL defines integral constants which are nothing but wrappers of an integral type and a value of
 * that type.
 * Example:
 * template <int N>
 * struct int_
 * {
 *     typedef int_<N> type;
 *     typedef int value_type;
 *     static const value_type value = N;
 *     operator int() {
 *         return value;
 *     }
 *
 *    // and some more details.
 * };
 */

#include <iostream>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/next_prior.hpp>
#include <cassert>

using namespace std;
namespace mpl = boost::mpl;

int main()
{
    typedef mpl::int_<8> eight;

    BOOST_MPL_ASSERT (( boost::is_same<eight::value_type, int> ));
    BOOST_MPL_ASSERT (( boost::is_same<eight::type, eight> ));
   
    cout << eight::value << endl; //should return 8
    cout << eight::type::value << endl; //should return 8

    BOOST_MPL_ASSERT (( boost::is_same< mpl::next<  eight  >::type, mpl::int_<9> > ));
    BOOST_MPL_ASSERT (( boost::is_same< mpl::prior< eight  >::type, mpl::int_<7> > ));

    BOOST_MPL_ASSERT_RELATION ( eight::value, ==, 8);

    assert (eight() == 8);    //possible because we have a conversion c'tor.

    return 0;
}

// Similarly u have types long_, bool_, char_, size_t
// Note for bool_, mpl defines typedef's
//
// typedef bool_<true> true_;
// typedef bool_<false> false_;
//
// Further we have another wrapper called integral_c <T, n>
//
// template <typename T, T n>
// struct integral_c {
//    ..
// };
// such that given "typedef integral_c<T, c> x;
// x::value_type is T and x::value == c.
//
// This means integral_c<int, 10> is same as int_<10>
// This means integral_c<bool, false> is same as bool_<false>

