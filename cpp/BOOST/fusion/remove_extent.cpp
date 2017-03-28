#include <iostream>
#include <string>
#include <array>
#include <typeinfo>
#include <utility>
#include <type_traits>
#include <cxxabi.h>

using std::cout;
using std::endl;
using std::string;

string demangle(const char* mangled_name) {
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
    typedef int array_2_3[2][3];
    cout << "array_2_3 type: " << demangle(typeid(array_2_3).name()) << endl;

    typedef std::remove_extent<array_2_3>::type one_bound_removed_type;
    cout << "array_2_3 type with first bound removed: " << demangle(typeid(one_bound_removed_type).name()) << endl;
    cout << "size of array_2_3: " << sizeof(array_2_3) << endl;
    cout << "size of array_2_3 after first bound removed: " << sizeof(one_bound_removed_type) << endl;
    cout << "Size of first bound: " << sizeof(array_2_3)/sizeof(one_bound_removed_type) << endl;

    typedef std::remove_extent<one_bound_removed_type>::type second_bound_removed_type;
    cout << "array_2_3 type with second bound removed: " << demangle(typeid(second_bound_removed_type).name()) << endl;
    cout << "size of array_2_3 after first bound removed: " << sizeof(one_bound_removed_type) << endl;
    cout << "size of array_2_3 after second bound removed: " << sizeof(second_bound_removed_type) << endl;
    cout << "Size of second bound: " << sizeof(one_bound_removed_type)/sizeof(second_bound_removed_type) << endl;

    return 0;
}
