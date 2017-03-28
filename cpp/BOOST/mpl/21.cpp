/*
 * Here we need to study applyn<>.
 * Before that we should know what is lambda<> and LAMBDA EXPRESSION.
 *
 * LAMBDA EXPRESSION -
 * A lambda expression is a compile time invocable entity of either of the two forms.
 *
 * 1) Metafunction class or
 * 2) Placeholder expression.
 *
 * This means that wherever you see LAMBDA EXPRESSION, it means either a metafunction class or placeholder expression.
 *
 * What applyn<> does is that it uses another meta-function called lambda<F> which takes a lambda expression and
 * 1) If F is a PLACEHOLDER EXPRESSION it returns a METAFUNCTION-CLASS embedding the PLACEHOLDER EXPRESSION INSIDE IT.
 * 2) If F is not a PLACEHOLDER EXPRESSION, returns F unchanged.
 *
 * So since lambda<F>::type, will/should always be a MC, applyn<F, A1,A2,..,An>::type is same as
 * apply_wrapn< lambda<F>::type, A1, A2, A3, .., An>::type
 * Where F is a lambda expression.
 *
 * Lets see examples.
 */

#include <iostream>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/placeholders.hpp>

namespace mpl = boost::mpl;

using namespace boost::mpl::placeholders;

// myplus_ is a metafunction.
template <typename N1, typename N2>
struct myPlus_ : public mpl::int_<N1::value + N2::value> {
};

/* since F below is a placefolder expression, apply2<> will internally do lambda<F>
   which will return a metafunction-class, something like below:

   struct some_meta_function_class {
       template <typename N1, typename N2>
       struct apply : public myPlus_<N1, N2> {
       }
    };

    and lambda<F>::type will be some_meta_function_class
    and apply2::type will be some_meta_function_class::apply<mpl::int_<2>, mpl::int_<3>>::type
*/
typedef mpl::apply2<myPlus_<_1, _2>, mpl::int_<2>, mpl::int_<3>>::type r1; 

// samething as above with apply_wrapn
typedef mpl::apply_wrap2<mpl::lambda<myPlus_<_1, _2>>::type, mpl::int_<2>, mpl::int_<3>>::type r2;

struct some_meta_function_class {
    template <typename N1, typename N2>
    struct apply : public myPlus_<N1, N2> {
    };
};

typedef mpl::apply_wrap2<some_meta_function_class, mpl::int_<2>, mpl::int_<3>>::type r3; 

int main() {
    BOOST_MPL_ASSERT (( boost::is_same <r1::value_type, int> ));
    BOOST_MPL_ASSERT (( boost::is_same <r1, r2> ));
    BOOST_MPL_ASSERT (( boost::is_same <r1, r3> ));
    BOOST_MPL_ASSERT (( boost::is_same <r1::type, mpl::int_<5>::type> ));
    BOOST_MPL_ASSERT_RELATION ( r1::value, ==, 5 );
    BOOST_MPL_ASSERT_RELATION ( r2::value, ==, 5 );
    BOOST_MPL_ASSERT_RELATION ( r3::value, ==, 5 );
    return 0;
}

/*
applyn<> is implemented using other metafunctions, protect<>. bind<> and quote<>
but lets not go too deep into those.
*/
