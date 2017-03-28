/*
front_extended_queue and back_extended_queue - These are fusion data structures which can be used to add new types to a deque data strcuture.
So If you have a deque data structure with types int, double; then you can create a new front_extended_queue data structure with a new type bool at the
front. With back_extended_queue the new type gets added at the back.

template <typename Deque, typename T>
class front_extended_queue

template <typename Deque, typename T>
class back_extended_queue
*/

#include <cxxabi.h>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/container/deque/back_extended_deque.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>
#include <string>
#include <cassert>
using std::cout;
using std::cin;
using std::endl;
using std::string;
namespace fusion = boost::fusion;
namespace mpl = boost::mpl;

string demangle(const char* mangled_name) {
    int status = -1;
    char* realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if (status == 0) {
        string result(realname);
        free(realname);
        return result;
    } else {
        string result(mangled_name);
        return result;
    }
}

struct print_xml {
    template <typename Type>
    void operator() (const Type& t) const {
        cout << "<" << demangle(typeid(t).name()) << ">"
             << t << "</" << demangle(typeid(t).name()) << ">" << endl;
    }
};

int main() {
    typedef fusion::deque<int, double> deck_type;
    deck_type d(10, 5.5);
    typedef fusion::front_extended_deque<deck_type, string> fed_type;
    fed_type fed(d, "Hello Front Extended Deque");
    cout << "Front Extended Deque" << endl;
    cout << fusion::at_c<0>(fed) << "  ";
    cout << fusion::at_c<1>(fed) << "  ";
    cout << fusion::at_c<2>(fed) << "  ";
    cout << "\n\n";
    cout << "Back Extended Deque" << endl;
    fusion::back_extended_deque<fed_type, string> bed(fed, "Hello Back Extended Deque");
    cout << fusion::at_c<0>(bed) << "  ";
    cout << fusion::at_c<1>(bed) << "  ";
    cout << fusion::at_c<2>(bed) << "  ";
    cout << fusion::at_c<3>(bed) << "  ";
    cout << endl;
}

/*
set and map are also very trivial.

fusion::set<int, double> d(10, 5.5f);
fusion::at_key<int>(d) = 10
fusion::at_key<double>(d) = 5.5

And map also you have seen before.
*/
