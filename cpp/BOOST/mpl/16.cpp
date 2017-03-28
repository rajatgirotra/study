/*
 * Same as 15.cpp except that we use BOOST_MPL_ASSERT 
 *
 * BOOST_MPL_ASSERT (( pred )) // two parantheses compulsory.
 * fails if pred::type::value == false
 */

#include <iostream>
#include <string>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp> // FOR BOOST_MPL_ASSERT
#include <boost/type_traits/is_same.hpp>
using namespace std;

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::identity<int>::type intMplType;
    typedef mpl::identity<const int>::type constIntMplType;
    typedef int intType;

    BOOST_MPL_ASSERT(( boost::is_same< intMplType, intType> ));
    BOOST_MPL_ASSERT(( b17oost::is_same< constIntMplType,intType> ));
    return 0;
}



