// fusion iterators and sequence functions
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/support.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

using std::cout;
using std::endl;
using std::string;
using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;
namespace fusion = boost::fusion;

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
    // You can always iterate using fusion::for_each() algorithm.
    // Here lets see some of the functions available to sequences and iterators
    typedef fusion::list<int, bool, double, char> list_type;
    list_type l(10, true, 5.5, 'A');

    // Sequence functions for forward sequence types- begin(), end(), size(), empty(), front()
    // fusion result_of is a namespace that helps you get the result types of various functions */
    typedef fusion::result_of::begin<list_type>::type begin_type;
    typedef fusion::result_of::end<list_type>::type end_type;
    cout << "begin_type = " << demangle(typeid(begin_type).name()) << endl;
    cout << "end_type = " << demangle(typeid(end_type).name()) << endl;
    cout << fusion::size(l) << endl;
    cout << std::boolalpha << fusion::empty(l) << endl;
    cout << fusion::front(l) << endl;

    // bidirectional sequence types also have - back() Eg: fusion::vector
    typedef fusion::vector<int, bool, double, char> vector_type;
    vector_type v(10, true, 5.5, 'A');
    cout << fusion::back(v) << endl;

    // random access iterators will support all of the above plus
    // at_c<N>, at<M> where N is int type and M is mpl::int_<> type

    // associative containers - set, map and others
    // You already know fusion sets and maps do not have any ordering of elements.
    // the key is a type as you saw before. They support above functions and
    // has_key<K> (returns true or false), at_key<S>.

    //iterator functions for forward iterator type
    /*
      next(i) where i is an iterator returned by begin()
      deref(i) or *i where i is an iterator
      advance_c<1> will return an iterator i advanced one step
      advance<M> - same as above but M should be of type int_<> from mpl
      distance(i, j) - will return an int_<> where int_<>::value will return the distance b/w i and j iterators.
      i == j
      i != j
      next(i) and advance_c<1> and advance<int_<1>> are all the same 
    */

    /* iterator functions for bidirectional iterator type
      same as above plus one more
      prior(i) -- will return an iterator to the previous element
    */

    /* random access iterators support
        deref_data(i) - where i is the associative iterator type
        It returns the value stored corresponding to the type referenced by the iterator
        You also have
        fusion::result_of::begin<Seq>::type first;
        fusion::result_of::key_of<first>::type; // will give you the type of the first template parameter to fusion::pair<>
        fusion::result_of::value_of_data<first>::type; // will give you the type of the second template parameter to fusion::pair<>
     */

    /* The swap(v1, v2) function swaps the two sequences v1 and v2. */
}
