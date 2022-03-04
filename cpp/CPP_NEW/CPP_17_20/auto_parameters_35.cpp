/*
 * C++20 allows function parameters (for ordinary functions and for member functions including operators) to be auto. Under the hood, actually its just a template function,
 * so the rules of template function apply. So
 *
 * void foo(const auto& arg) is nothing but a shorthand for
 *
 * template <typename T>
 * void foo(const T& arg)
 *
 * Since it is a function template really, you must implement it in the header file itself.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void printCollection(const auto& coll) {
    for (auto&& item : coll) {
        cout << item << endl;
    }
}

class Username {
    string m_user {};

public:
    Username(string arg) : m_user(std::move(arg)) {}
    const string& getName() const noexcept { return m_user; }

    auto operator <=> (const Username& rhs) const noexcept {
        return this->getName() <=> rhs.getName();
    }
};

bool lessByNameFunc(const auto& c1, const auto& c2)  {
    return c1.getName() < c2.getName();
}

auto lessByNameLambda = [] (const auto& c1, const auto& c2)  {
    return c1.getName() < c2.getName();
};

void printArg(auto&& arg) {
    cout << std::boolalpha << arg << endl;
}
// auto... Args is also allowed
void printArgs(auto... args) {
    (printArg(args), ...);
}


int main() {
    std::vector<double> dVec {1., 2., 3., 4.};
    printCollection(dVec);
    printCollection(string("Hello"));

    std::vector<Username> uVec {Username("Rajat"), Username("Vidhu"), Username("Myra"), Username("Viraj")};

    // This doesnt work as the underlying is a function template. with function templates, you need to specify the template parameter also.
    // and for this shorthand notation, we dont have access to the template parameter T.
//    std::sort(uVec.begin(), uVec.end(), lessByNameFunc);

    std::sort(uVec.begin(), uVec.end(), lessByNameLambda);

    for(auto&& item : uVec) {
        cout << item.getName() << endl;
    }

    printArgs(1, 2., true, string("HelloWorld"));
}
