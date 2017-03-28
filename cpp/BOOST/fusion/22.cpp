/*
Boost fusion defines macros that can be used to make any arbitrary structure a model of a Random access sequence.
Basically it generates all the boilerplate code for enabling reflections in C++.
*/
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/mpl/vector.hpp>
#include <iostream>
#include <string>
#include <array>
#include <cxxabi.h>
#include <typeinfo>
#include <utility>
using std::cout;
using std::endl;
using std::string;

namespace mpl = boost::mpl;
namespace fusion = boost::fusion;

string demangle(char* mangled_name) {
    int status = -1;
    char* realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if (status == 0) {
        string name(realname);
        free(realname);
        return name;
    } else {
        return string(mangled_name);
    }
}

struct print_xml {
    template <typename T>
    void operator() (const T& t) {
        cout << "<" << demangle(typeid(T).name()) << ">"
             << t << "</" << demangle(typeid(T).name()) << ">"
             << endl;
    }
};


namespace demo {
    struct employee {
        string name;
        int age;
    };

    template <typename Name, typename Age>
    struct candidate {
        Name name;
        Age age;
        uint64_t nanos;
    };
}

// Use this macro to adapt an already defined structure.
// Use this macro always at the global scope and structure name should be namespace qualified.
BOOST_FUSION_ADAPT_STRUCT(
    demo::employee,
    (BOOST_FUSION_ADAPT_AUTO, name)
    (BOOST_FUSION_ADAPT_AUTO, age)
)

// When the structure is a template, use BOOST_FUSION_ADAPT_TPL_STRUCT
BOOST_FUSION_ADAPT_TPL_STRUCT(
    (Name)(Age), // template parameters
    (demo::candidate)(Name)(Age),
    (Name, name)
    (Age, age)
    (BOOST_FUSION_ADAPT_AUTO, nanos)
)

int main() {
    demo::employee e {"Rajat", 32};
    cout << fusion::deref(fusion::begin(e)) << endl;
    cout << fusion::at_c<1>(e) << endl;
    cout << fusion::back(e) << endl;
    cout << *fusion::advance_c<0>(fusion::begin(e)) << endl;

    cout << endl;
    demo::candidate<string, double> c {"Vidhu", 31.5, 1234567893};
    cout << fusion::deref(fusion::begin(c)) << endl;
    cout << fusion::deref(fusion::prior(fusion::end(c))) << endl;
    cout << fusion::deref(fusion::next(fusion::begin(c))) << endl;
    cout << fusion::at_c<1>(c) << endl;
    cout << fusion::back(c) << endl;
    cout << *fusion::advance_c<0>(fusion::begin(c)) << endl;
    return 0;
}

/* 
There are a number of variations available for this macro.
We will not go thru each. They are trivial to understand if you understand
the basic ones. The important one is BOOST_FUSION_DEFINE_STRUCT
and BOOST_FUSION_DEFINE_STRUCT_INLINE
*/
