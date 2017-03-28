// tie functions for easy unpacking of fusion sequences
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container/generation/make_map.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
namespace fusion = boost::fusion;
namespace mpl = boost::mpl;

struct int_key;
struct double_key;

int main() {
    auto l = fusion::make_list(10, true, 5.5);
    auto c = fusion::make_cons(20.4, fusion::make_cons(true));
    auto v = fusion::make_vector(5.5, 'a', "Hello");
    auto dbl = fusion::make_deque(10, true, 5.5);
    auto s = fusion::make_set(10, true, 5.5);

    auto m = fusion::make_map<int, double>(10, 5.5);
    // OR
    //fusion::result_of::make_map<int_key, double_key>::apply<int, double>::type m2 = fusion::make_map<int, double>(10, 5.5);


    int i = 0;
    bool b = false;
    double d = 0.0;

    /* vector_tie() is a function which takes lvalues as arguments and returns a vector whose types are references to those
    values. so vector_tie(i, b, d) returns a fusion::vector<int&, bool&, double&> where int& is a reference to i, bool& is a refernce to b
    and double& is a refernce to d. */
    fusion::vector_tie(i, b, d) = l;  // this will assign 10 to i, true to b and 5.5 to d.
    cout << i << " " << std::boolalpha << b << " " << d << endl;

    // similary we have list_tie(), deque_tie(), map_tie()

    // map tie is slightly different. fusion::map() does not have an assignment operator, so i have to assign values manually.
    // i = -89, d = 9.9
    auto x = fusion::map_tie<int_key, double_key>(i, d); // x now holds references to i and d.
    //OR
    //fusion::result_of::map_tie<int_key, double_key, int, double>::type x2 = fusion::map_tie<int_key, double_key>(i, d);
    i = -89; d = 9.9;
    cout << fusion::at_key<int_key>(x) << " "
         << fusion::at_key<double_key>(x) << endl;
    return 0;
}

// instead of auto you could also use fusion::result_of::make_vector<>::type and so on for others.
