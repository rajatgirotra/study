// some functions for easily creating make_list(), make_vector() etc..
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
namespace fusion = boost::fusion;
namespace mpl = boost::mpl;

int main() {
    auto l = fusion::make_list(10, true, 5.5);
    auto c = fusion::make_cons(20.4, fusion::make_cons(true));
    auto v = fusion::make_vector(5.5, 'a', "Hello");
    auto d = fusion::make_deque(10, true, 5.5);
    auto s = fusion::make_set(10, true, 5.5);
    auto m = fusion::make_map<int, double>(10, 5.5);
    return 0;
}

// instead of auto you could also use fusion::result_of::make_vector<>::type and so on for others.
