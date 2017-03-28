/*
adapting an std::tuple
*/
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/mpl/vector.hpp>
#include <iostream>
#include <string>
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


int main() {
    std::tuple<int, char, double, bool> p(10, 'A', 2.3, true);
    cout << fusion::at<mpl::int_<0>>(p) << endl;
    cout << fusion::at_c<1>(p) << endl;
    cout << fusion::at<mpl::int_<2>>(p) << endl;
    cout << fusion::at<mpl::int_<3>>(p) << endl;
    cout << fusion::deref(fusion::next(fusion::begin(p))) << endl;
    cout << fusion::back(p) << endl;
    return 0;
}
