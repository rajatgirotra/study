/*
 * Understanding view caching further. Let's try to see actually what happens under the hood when we print a view.
 * Some view vColl
 * for(auto iter = vColl.begin(); iter != vColl.end(); ++iter) {
 *    cout << *iter << endl;
 * }
 *
 * We will actually code up this for loop manually.
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

    // let's manually iterate the view
    int elem{};
    cout << "\nStarting to iterate view";
    auto iter = values.begin();
    cout << "\niter initialized";
    cout << "\n****************************";
    cout << "\ncalculating element:";
    elem = *iter;
    cout << "\nelement calculated: " << elem;
    cout << "\nbefore incrementing iter";
    ++iter;
    cout << "\nafter incrementing iter";
    if (iter == values.end()) { cout << "\niteration complete"; exit(0); }
    cout << "\n****************************";
    cout << "\ncalculating element:";
    elem = *iter;
    cout << "\nelement calculated: " << elem;
    cout << "\nbefore incrementing iter";
    ++iter;
    cout << "\nafter incrementing iter";
    if (iter == values.end()) { cout << "\niteration complete"; exit(0); }
    cout << "\n****************************";
    cout << "\ncalculating element:";
    elem = *iter;
    cout << "\nelement calculated: " << elem;
    cout << "\nbefore incrementing iter";
    ++iter;
    cout << "\nafter incrementing iter";
    if (iter == values.end()) { cout << "\niteration complete"; exit(0); }
    cout << "\n****************************";
    cout << "\ncalculating element:";
    elem = *iter;
    cout << "\nelement calculated: " << elem;
    cout << "\nbefore incrementing iter";
    ++iter;
    cout << "\nafter incrementing iter";
    if (iter == values.end()) { cout << "\niteration complete"; exit(0); }
    cout << "\n****************************";
    cout << "\ncalculating element:";
    elem = *iter;
    cout << "\nelement calculated: " << elem;
    cout << "\nbefore incrementing iter";
    ++iter;
    cout << "\nafter incrementing iter";
    if (iter == values.end()) { cout << "\niteration complete"; exit(0); }

}

/*
* When we call begin(), the following happens:
– The request to get the first element of vColl is passed to the transform view, which passes it to the
filter view, which passes it to coll, which yields an iterator to the first element 8.
– The filter view looks at the value of the first element and rejects it. As a consequence, it asks coll for
the next element by calling ++ there. The filter gets the position of the second element 15 and passes
its position to the transform view.
– As a result, iter is initialized as an iterator with the position to the second element.

When calling *iter, the following happens:
– Because we need the value, the transform view is now called for the current element and yields its
negated value.
– As a result, elem is initialized with the negated value of the current element.

When calling ++iter, the same happens again:
– The request to get the next element is passed to the filter, which passes the request to coll until an
element fits (or we are at the end of coll).
– As a result, iter gets the position of the fourth element.
• By calling *iter again, we perform the transformation and yield the next value for the loop.
This iteration continues until the range or one of the views signals that we are at the end.

The reason C++ implements it this way is for optimization purposes. This pull model has a big benefit: we do not process elements that we never need.
For example, assume that we use the view to find the first resulting value that is 0, using rng::find(vColl, 0). then the output would be:
filter 8
filter 15
trans 15
filter 7
filter 0
trans 0

So you must remember how a view calculates its values. they first compute the position/iterator (with begin() and ++),
and then as a separate step, use * operator to get the value.

Now in the next example, just reverse the filter and transform adaptors (put transform first and filter second). and try to see if you can
understand the output.
 */