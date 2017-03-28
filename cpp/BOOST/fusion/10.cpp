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
    typedef map<pair<fields::name, string>, pair<fields::age, int> > person_t;
    person_t myMap(make_pair<fields::name>("Rajat"), make_pair<fields::age>(32));

    fusion::result_of::deref_data<fusion::result_of::begin<person_t>::type >::type val = fusion::deref_data(fusion::begin(myMap));
    cout << val << endl;

    // For each will return a fusion::pair<> to the print_xml() function.
    // Note also how in print_xml, outputting the fusion::pair to the ostream correctly prints the data stored in that pair.
    fusion::for_each(myMap, print_xml());

    cout << endl << "Swap" << endl;
    fusion::vector<int, string> v1(1, "Hello");
    fusion::vector<int, string> v2(2, "World");
    fusion::swap(v1, v2);
    cout << fusion::at_c<0>(v1) << " " << fusion::at_c<1>(v1) << endl; // should be 2 World
    return 0;
}
