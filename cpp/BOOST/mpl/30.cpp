#include <iostream>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/integral_c.hpp>
#include <typeinfo>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
using namespace std;
namespace mpl = boost::mpl;

struct A
{
    typedef A type;
};

template <typename T>
class B
{
    public:
        typedef T type;
};

int main()
{
    BOOST_MPL_ASSERT (( boost::is_same<mpl::identity<int>::type, int> ));

    cout << mpl::plus < mpl::int_<10>, mpl::int_<-9>, mpl::long_<123> >::type::value << endl;
    cout << typeid(mpl::plus < mpl::int_<10>, mpl::int_<-9>, mpl::long_<123> >::value_type).name() << endl; //Long

    typedef mpl::vector<A, B<double> > v; 

    //mpl::vector<A, B> v1; //Wont compile, see the minute difference, B is a class template, it is not a type.
                            //But when it is instantiated ie. B<double>, it becomes a type.
                     
    typedef mpl::begin< v >::type iter;
    BOOST_MPL_ASSERT (( boost::is_same <mpl::deref<iter>::type, A::type> ));
    BOOST_MPL_ASSERT (( boost::is_same <mpl::deref<iter>::type, A> ));
    BOOST_MPL_ASSERT (( boost::is_same <mpl::deref< mpl::next<iter>::type >::type::type, double> )); //Kya baat..
} 
