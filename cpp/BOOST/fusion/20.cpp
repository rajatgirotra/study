/* fusion adapted. fusion provides adaptor classes to treat a number of other types as first class fusion sequences.
like:
   std::array, boost::array
   C-arrays
   std::pair
   std::tuple, boost::tuple
   mpl sequences
   General structues
  
   Lets start seeing them in action
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
    // Adapt a simple array as a fusion sequence - It becomes a Random Access Sequence.
    const char* names[] { "Rajat", "Vidhu", "Myra", "SHRI RAM"};
    cout << "\nAdapting plain Array" << endl;
    cout << *fusion::begin(names) << endl;  // begin returns an iterator and we deref it.
    cout << *fusion::next(fusion::begin(names)) << endl;
    cout << *fusion::advance_c<3>(fusion::begin(names)) << endl;
    cout << fusion::at<mpl::int_<1>>(names) << endl; // returns a const char* and we print it as is.
    cout << fusion::at_c<1>(names) << endl;
    cout << *fusion::prior(fusion::prior(fusion::end(names))) << endl;

    // Adapt an std pair as a fusion sequence - It becomes a Random access sequence.
    cout << "\nAdapting std::pair" << endl;
    typedef std::pair<double, char> stdpair_t;
    stdpair_t stdpair(10.5, 'x');
    cout << *fusion::begin(stdpair) << endl;
    cout << *fusion::next(fusion::begin(stdpair)) << endl;
    cout << *fusion::advance_c<1>(fusion::begin(stdpair)) << endl;
    cout << *fusion::prior(fusion::prior(fusion::end(stdpair))) << endl;
    return 0;
}
