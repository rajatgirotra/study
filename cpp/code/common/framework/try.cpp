#include <iostream>
#include <string>
#include <common/framework/utils/demangle.hpp>
#include <common/framework/exception/exception.hpp>
#include <typeinfo>

using namespace std;

namespace {
    template <typename T, unsigned int N>
    class A{};
};

int main()
{
    try {
        A<double, 19> a;
        cout << common::framework::utils::demangle(typeid(a).name()) << endl;
        cout << common::framework::utils::demangle("ABCD") << endl;
    } catch(const boost::exception& e) {
        cout << boost::diagnostic_information(e) << endl;
    }
    return 0;
}

