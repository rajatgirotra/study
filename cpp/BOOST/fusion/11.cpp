// Getting the type of the types in a vector - using fusion::result_of::value_of<Iterator_type>::type
#include <cxxabi.h>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <iostream>
#include <string>
using std::cout;
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
    typedef fusion::vector<string, int> person_t;
    typedef fusion::result_of::begin<person_t>::type first;
    typedef fusion::result_of::next<first>::type second;
    typedef fusion::result_of::value_of<first>::type first_value_type;
    typedef fusion::result_of::value_of<second>::type second_value_type;
    cout << std::boolalpha << boost::is_same<first_value_type, string>::value << endl;
    cout << std::boolalpha << boost::is_same<second_value_type, int>::value << endl;
    return 0;
}
