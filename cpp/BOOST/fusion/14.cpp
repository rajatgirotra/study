// Fusion sequences like vector, list and deque can also be stored as keys of boost::unordered_map/set.
// How remembr that for a type to be a key of an unordered map/set, it must provide a function for hash_value() calculation
// and a function for comparison. for boost::unordered_map, we must have a hash_value() function and == operator.
// both these are provided by fusion. Fusion provides a function boost::fusion::hash_value(Seq) which takes a seq,
// calculates a hash for each individual element and returns a combined hash.
#include <cxxabi.h>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/include/hash.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>
#include <string>
#include <cassert>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using boost::fusion::pair;
using boost::fusion::map;
using boost::fusion::make_pair;
namespace fusion = boost::fusion;

namespace fields {
    struct name;
    struct age;
};

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
    typedef fusion::vector<string, int> vector_type;
    const vector_type v {"Hello", 10};
    cout << fusion::hash_value(v) << endl;

    boost::unordered_map<vector_type, string> myMap;
    myMap[v] = "World";
    assert(myMap.size() == 1 && myMap.count(v) == 1);
    return 0;
}
