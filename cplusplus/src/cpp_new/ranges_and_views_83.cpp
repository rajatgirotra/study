/*
 * View caching and consequences.
 */
#include <iostream>
#include <concepts>
#include <ranges>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cxxabi.h>
#include <cassert>
#include <random>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

string demangle(const char* const mangled_name) {
    int res = -1;
    auto str = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
    assert(res == 0);
    string ret(str);
    free(str);
    return ret;
}

int main() {

    // 1st exmaple.
    std::vector<int> coll {8, 15, 7, 0, 9};

    // create a view with only numbers which are multiple of 3, then return the negative of that number
    auto values = coll
        | vws::filter([](auto&& elem) { cout << "\nfilter: " << elem; return elem %3 == 0;})
        | vws::transform([](auto&& elem) { cout << "\n\ttrans: " << elem; return elem * -1;});

    // now iterate the view do nothing in the for loop
    cout << "\nvalues | filter | transform";
    for (auto&& _ : values) {}
    cout << "\n****************************";

    // iterate again and note the output.
    cout << "\nvalues | filter | transform";
    for (auto&& elem : values) {
        cout << "\n\t\tvalue: " << elem;
    }


    cout << "\n****************************  2nd example";
    // 2nd example:
    std::vector vec{1, 2, 3, 4};
    auto biggerThan2 = [](auto v){ return v > 2; };
    auto vVec = vec | std::views::filter(biggerThan2);
    cout << endl;
    rng::copy(vVec, ostream_iterator<int>(cout, " "));
    cout << endl;

    ++vec[1];
    vec[2] = 0;// vec becomes 1 3 0 4
    rng::copy(vVec, ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << "\n****************************";
}

/* What is happening. basically the "values" view is caching its begin() iterator on the first pass.
 * Then in the second pass, it does not need to start at the beginning again. This is just an optimization
 * in the view implementation.
 *
 * Note that this caching of begin() has good and bad and maybe unexpected consequences. What you have to remember is not to modify
 * the collection after the view has cached the begin() iterator. Example:
 *
 * std::list intList {1, 2, 3, 4, 5};
 * auto vColl = intList | vws::drop(2); // this is ok. begin iterator is not cached here.
 * intList.push_front(0); // still ok as modification is done before view caches begin iterator.
 * print(vColl); //print is a function which iterator the view and prints each value. definitely init() happens here & 2, 3, 4, 5 will be printed.
 *
 * std::list intList {1, 2, 3, 4, 5};
 * auto vColl = intList | vws::drop(2); // this is ok. begin iterator is not cached here.
 * print(vColl); //caching happens here. begin iterator will point to 3.
 * intList.push_front(0);
 * print(vColl); // careful!! still 3, 4, 5, will be printed.
 */