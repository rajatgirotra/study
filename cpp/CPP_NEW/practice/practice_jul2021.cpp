#include "practice_jul2021.hpp"
#include <type_traits>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <map>
using namespace std;

[[maybe_unused]] const int* p = &mystruct::m_value;
//constexpr int mystruct::m_value {99};

const char* pi_function(int index) {
    static constexpr char name[] {"Rajat"};
    return (name + index);
}

template <typename BDIter>
void alg(BDIter,  BDIter , std::bidirectional_iterator_tag) {
    cout << "alg for list\n";
}

template <typename RAIter>
void alg(RAIter, RAIter, std::random_access_iterator_tag) {
    cout << "alg for vector\n";
}

template <typename Iter>
void alg(Iter begin, Iter end) {
    alg(begin, end, typename Iter::iterator_category{});
}


void trim([[maybe_unused]] string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [] (const char& ch){
        return !std::isspace(ch);}
        ));

    s.erase(std::find_if(s.rbegin(), s.rend(), [] (const char& ch){
        return !std::isspace(ch);}).base(), s.end());
}

void func(const char* s) {
    cout << "func(s) with s: " << s << endl;
}

template <typename... Args>
auto generic_lambda = [] (Args&&... args) {
    func(std::forward<Args>(args)...);
};

auto variadic_lambda = [] (auto&&... args) {
    func(std::forward<decltype(args)>(args)...);
};

struct X {
    int m_x;
};

static constexpr auto getValue = [](const X& x) {
    return x.m_x;
};


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    constexpr int constexpr_3 = 3;
    const int const_3 = 3;
    static_assert(constexpr_3 == const_3, "integral constexpr_3 == const_3");
    [[maybe_unused]] char char_array1[constexpr_3] {};
    [[maybe_unused]] char char_array2[const_3] {};

    [[maybe_unused]] constexpr double constexpr_half = 0.5;
    [[maybe_unused]] const double const_one_half = 1.5; // only integral constexpr values are really constant at compile time.
//    static_assert(constexpr_half < const_one_half); // this line will fail to compile. So you see a difference between const and constexpr

    constexpr char name[] = "Rajat";
    static_assert(name[2] == 'j', "index 2 must be j!");

    cout << *(pi_function(2));

    vector<string> vs;
    list<double> ld;
    alg(vs.begin(), vs.end());
    alg(ld.begin(), ld.end());

    string s = "               Hello             ";
    trim(s);
    cout << "trimmed string: " << s << " another string\n";

    variadic_lambda("Hello World with variadic lambda");
    generic_lambda<const char *>("Hello World with generic lambda");

    std::map<string, X> mymap{ {"Rajat", {38}}, {string("Vidhu"), {37}}};

    cout << getValue(mymap["Rajat"]) << endl;

}
