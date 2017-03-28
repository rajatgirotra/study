/* 
 * Some very important stuff to follow.
 *
 * 1) A placeholder
 *
 * A placeholder is just a typedef for the template argument number.
 *
 * typedef arg<1> _1; //meaning argument number 1.
 * typedef arg<2> _2; //meaning argument number 2.
 * typedef arg<3> _3; // ditto
 * .....
 * typedef arg<n> _n; where n is BOOST_MPL_LIMIT_METAFUNCTION_ARITY
 *
 *
 * Always say using namespace boost::mpl::placeholders; to use _1, _2, etc..
 * See example below
 *
 * Before we see placeholders, we'll see two more simple metafunctions.
 *
 * PLACEHOLDER EXPRESSION
 *
 * A placeholder expression is a type that is either a placeholder (_1, _2 etc) or
 * is a template specialization with atleast one argument that itself is a PLACEHOLDER EXPRESSION.
 * Eg:
 * _
 * _1
 * _2
 * plus<_, int_<2> >
 *
 * 
 * Metafunction - You already know this. A class or class template with a nested typedef with name "type"
 *
 * Metafunction class - A metafunction class is a class or class template with a nested metafunction called "apply".
 * This is used in high-order template metaprogramming as you will see later.
 *
 *
 * So remember both what is a PLACEHOLDER EXPRESSION and WHAT IS A METAFUNCTION CLASS.
 * 
 * Lambda Expression - When you see the term "Lambda expression" it means either a PLACEHOLDER EXPRESSION
 * or a METAFUNCTION CLASS. It can refer to either of them. A NUMBER OF high-order metafunctions take lambda expressions
 * as a template parameter; this means that it can be a placeholder expression or a metafunction class
 *
 * apply<> and apply_wrap<>.
 * Both these metafunctions must be in used in variadic forms,
 * ie applyn<F, A1, A2.. An> and apply_wrapn<F, A1, A2.. , An>
 *
 * apply_wrapn<F, A1, A2, .., An> - Very simple, when you are sure that F is a METAFUNCTION CLASS; you can call
 * apply_wrapn. It just calls F::apply with arguments A1, A2, .. , An
 *
 * If you are not sure if F is a METAFUNCTION CLASS or a PLACEHOLDER EXPRESSION, you can use applyn<> instead.
 * We'll see later what applyn<> does to figure out if F is a PE or a MC.
 *
 */
#include <iostream>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace mpl = boost::mpl;

struct f0
{
    struct apply
    {
        typedef char type;
    };
};

struct g0
{
    template <typename T = int>
    struct apply
    {
        typedef T type;
    };
};

struct f2
{
    template <typename T1, typename T2>
    struct apply
    {
        typedef T2 type;
    };
};

typedef mpl::apply_wrap0<f0>::type r1;
typedef mpl::apply_wrap1<g0, double>::type r2;
typedef mpl::apply_wrap2<f2, int, char>::type r3;
typedef mpl::apply2<f2, int, char>::type r4;

int main()
{
    BOOST_MPL_ASSERT (( boost::is_same <r1, char> ));
    BOOST_MPL_ASSERT (( boost::is_same <r2, double> ));
    BOOST_MPL_ASSERT (( boost::is_same <r3, char> ));
    BOOST_MPL_ASSERT (( boost::is_same <r4, char> ));
    return 0;
}

