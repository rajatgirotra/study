/*
 * std::optional is a wrapper type to express "nullable" types. before optional, a developer could represent a variable
 * as unset using values like -1, false, NULL etc. std::optional is an attempt to standardize that.
 *
 * The big thing to remember with std::optional is that it will not do any dynamic allocation for you. this means.
 * std::optional<int32_t>, will be at least 4 bytes + any information to keep track whether that int32_t is set or not.
 *
 * If set, it will destroy the int32_t when std::optional<> variables goes out of scope and its lifetime ends.
 */

#include <iostream>
#include <string>
#include <optional>
#include <cstdint>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct UserName {
private:
    string m_user;
public:
    explicit UserName(string arg = string("Rajat Girotra")) : m_user(std::move(arg)) {}

    friend ostream& operator << (ostream& os, const UserName& rhs) {
        return os << rhs.m_user;
    }
};

struct S {
    S() {
        cout << "S::ctor\n";
    }

    ~S() {
        cout << "S::dtor\n";
    }

    S(const S&) {
        cout << "S::copy ctor\n";
    }

    S& operator = (const S&) {
        cout << "S::copy assignment\n";
        return *this;
    }

    S(S&&)  noexcept {
        cout << "S::move ctor\n";
    }

    S& operator = (S&&)  noexcept {
        cout << "S::move assignment\n";
        return *this;
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::optional<int32_t> i;
    cout << "sizeof(std::optional<int32_t>): " << sizeof(i) << endl;

    try {
        // accessing an unset optional throws "bad optional access"
        cout << "std::optional<int32_t>::value: " <<  i.value() << endl;
    } catch(const std::exception& e) {
        cerr << "exception caught printing std::optional<int32_t>::value, error: " << e.what() << endl;
    }

    i = 10; // performs assignment
    cout << "std::optional<int32_t>::value: " <<  *i << endl; // should print 10

    i.reset();
    cout << "std::optional<int32_t>::has_value(): " << i.has_value() << ", std::optional<int32_t>::value_or(): " <<  i.value_or(99) << endl; // will print 99

    // other ways to create optional.
    std::optional<int> emptyOpt;
    [[maybe_unused]] std::optional<double> emptyDouble = std::nullopt;

    // direct
    std::optional<int> iOpt(-123);

    // use make_optional()
    [[maybe_unused]] auto x = std::make_optional(-5.5); // x is std::optional<double>

    // in_place. (just like std::piecewise_construct, forwards the arguments to the underlying)
    std::optional<std::vector<int>> optVec (std::in_place, {1, 2, 3});
    std::copy(optVec->begin(), optVec->end(), std::ostream_iterator<int>(cout, " "));

    // construct a std::optional<UserName> (tricky)
    std::optional<UserName> user; // doesnt work. user will be unset ie std::nullopt
    std::optional<UserName> user2{UserName()}; // this works but you create a temporary.
    std::optional<UserName> user3{std::in_place}; // this works
    cout << endl;

    {
        std::optional<S> optS1;
        S objS;
        cout << endl;
        optS1 = objS; // copy ctor
        optS1 = objS; // 2nd time onwards it performs copy assignment.
    }
    // but what if your type doesn't have a move or copy operation. or you want to avoid the cost of move or copy
    // for that optional provides emplace() api
    cout << "\ndoing emplace now\n";
    std::optional<S> optS2;
    optS2.emplace();

    cout << "\nstd::optional<> supports comparisons also\n";
    {
        std::optional<int> oEmpty;
        std::optional<int> oTwo(2);
        std::optional<int> oTen(10);
        cout << std::boolalpha;
        cout << (oTen > oTwo) << '\n'; // expected
        cout << (oEmpty < oTwo) << '\n'; // std::nullopt is always less than std::optional<> which has value
        cout << (oEmpty == std::nullopt) << '\n';
        cout << (oTen == 10) << '\n';
    }

    return 0;
}
