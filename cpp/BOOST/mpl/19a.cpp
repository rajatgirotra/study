/*
 * Just like plus, we'll look at some of the other numeric metafunctions here
 */

#include <iostream>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/negate.hpp>
#include <boost/mpl/times.hpp>

using namespace std;
namespace mpl = boost::mpl;

int main()
{
    /** minus<>, the template parameters must be integral constants **/
    typedef mpl::minus< mpl::int_<-10>, mpl::int_<30> >::type r;
    BOOST_MPL_ASSERT(( boost::is_same<r::type, mpl::integral_c<int, -40> > ));
    BOOST_MPL_ASSERT_RELATION( r::value, ==, -40 );

    /* negate<>, very simple, yields the same type but with the wrapped value multiplied by -1. */
    typedef mpl::negate<mpl::integral_c<int, -10> >::type n;
    BOOST_MPL_ASSERT (( boost::is_same<n::type, mpl::integral_c<int, 10>::type > ));
    BOOST_MPL_ASSERT (( boost::is_same<n::type, mpl::integral_c<int, 10> > )); //because integral_c<>::type and integral_c are same types.
    BOOST_MPL_ASSERT (( boost::is_same<n::value_type, mpl::integral_c<int, 10>::value_type > ));
    BOOST_MPL_ASSERT_RELATION ( n::value, ==, 10 );

    /* Same way, you also have times, yields the same type but the wrapped values multiplied */
    typedef mpl::times<mpl::integral_c<int, -10>, mpl::int_<100>, mpl::integral_c<long, 2> >::type t;
    BOOST_MPL_ASSERT (( boost::is_same<t::type, mpl::integral_c<long, -2000>::type > ));
    BOOST_MPL_ASSERT (( boost::is_same<t::type, mpl::integral_c<long, -2000> > ));
    BOOST_MPL_ASSERT (( boost::is_same<t::value_type, mpl::integral_c<long, 10>::value_type > ));
    BOOST_MPL_ASSERT_RELATION ( t::value, ==, -2000 );
 

    /** begin<X>, 
     * If X is a sequence, returns an iterator to the first element in the sequence X
     * If X is a NOT A sequence, returns void_
     */
    typedef mpl::vector<unsigned char, double, short, unsigned long long> sequence_type; //create a sequence.
    typedef mpl::begin< sequence_type >::type iterator_type;
    typedef mpl::deref< iterator_type >::type first_element_type;
    BOOST_MPL_ASSERT (( boost::is_same<first_element_type, unsigned char> ));
    BOOST_MPL_ASSERT (( boost::is_same<mpl::deref<mpl::begin<int>::type>::type, mpl::void_> ));

    /* Similar to above, we have end<X> also. Note that just like normal iterators
     * end also points to one past the last element. So we have to use prior<> here.
     */
    typedef mpl::end< sequence_type >::type end_iterator_type; //this will be void_
    typedef mpl::prior< end_iterator_type >::type last_iterator_type;
    typedef mpl::deref< last_iterator_type >::type last_element_type;
    BOOST_MPL_ASSERT (( boost::is_same<last_element_type, unsigned long long> ));
    BOOST_MPL_ASSERT (( boost::is_same<mpl::deref<mpl::end<long>::type>::type, mpl::void_> ));
    

    return 0;
}
