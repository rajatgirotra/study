// I/O - input output is very simple. 
#include <cxxabi.h>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <iostream>
#include <string>
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
    typedef fusion::vector<string, int, bool> person_t;
    person_t p("How are u?", 10, true);
    cout << p << endl;
    // You can further control the output using tuple_open, tuple_close and tuple_delimiter.
    cout << fusion::tuple_open("[ ") << fusion::tuple_close(" ]") << fusion::tuple_delimiter(", ") << p << endl;

    //Similarly for cin
    fusion::vector<int, string, double> vector_type_1;
    fusion::vector<bool> vector_type_2;
    cin >> vector_type_1;
    cin >> fusion::tuple_open('[') >> fusion::tuple_close(']') >> fusion::tuple_delimiter(':');
    cin >> vector_type_2;

    cout << "\nOutput" << endl;
    cout << vector_type_1 << endl;
    cout << vector_type_2 << endl;
    return 0;
}
