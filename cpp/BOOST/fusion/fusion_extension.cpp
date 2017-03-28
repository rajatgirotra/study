/* Boost fusion enables reflections in C++ by adding all the boilerplate
code behind the scenes and gives you a clean interface.

reflections means knowing the type of the variable, the name of the variable and its value all at compile time.
*/

#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/next_prior.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

namespace fusion = boost::fusion;
namespace mpl = boost::mpl;
using namespace std;

string demangle(const char* mangled_name) {
    int status = -1;
    char* realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if (status == 0) {
        string demangle_name(realname);
        free(realname);
        return demangle_name;
    } else {
        string demangle_name(mangled_name);
        return demangle_name;
    }
}

// template parameter S is a BOOST FUSION ADAPTED SEQUENCE LIKE A SIMPLE STRUCTURE
// template parameter N is an index into this sequence. N should be of type boost::mpl::int_
template <typename S, typename N>
struct element_at {
    // Type of element at this index.
    typedef typename fusion::result_of::value_at<S, N>::type type;

    // index of previous and next elements.
    typedef typename mpl::prior<N>::type previous;  // previous is of type boost::mpl::int_<>
    typedef typename mpl::next<N>::type next;

    // member name of the element at this index - name of the variable using boost fusion
    static inline string name() {
        return fusion::extension::struct_member_name<S, N::value>::call();
    }

    // type of element at this index - using demangle() from cxxabi.h
    static inline string type_name() {
        return demangle(typeid(type).name());
    }

    // get the actual value of the variable
    static inline typename fusion::result_of::at<const S, N>::type get(const S& s) {
        return fusion::at<N>(s);
    }
};

struct Inner {
    int a;
    double b;
    bool c;
};

BOOST_FUSION_ADAPT_STRUCT(
    Inner,
    (BOOST_FUSION_ADAPT_AUTO, a)
    (BOOST_FUSION_ADAPT_AUTO, b)
    (BOOST_FUSION_ADAPT_AUTO, c)
)


int main() {
    Inner inner {10, 23.6, true};
    cout << element_at<Inner, mpl::int_<0>>::name() << endl;
    cout << element_at<Inner, mpl::int_<0>>::type_name() << endl;
    cout << element_at<Inner, mpl::int_<0>>::get(inner) << endl;
    return 0;
}
