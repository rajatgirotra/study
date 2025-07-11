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
        | vws::transform([](auto&& elem) { cout << "\ntrans: " << elem; return elem * -1;})
        | vws::filter([](auto&& elem) { cout << "\n\tfilter: " << elem; return elem %3 == 0;});

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
– The request to get the first element of vColl is passed to the filter view, which passes it to the
transform view, which passes it to coll, which yields an iterator to the first element 8. the transform view return -8 to filter view.
– The filter view looks at the value -8 and rejects it. this causes the next value to be transformed and returned to filter view i.e. -15.
- this value passes the filter so the initialization stops here.
– As a result, iter is initialized as an iterator with the position to the second element.

When calling *iter, the following happens:
– The filter view only caches the iterator the element in vColl, it doesn't cache the result of the transform.
- so *iter causes another call to the transform function and then -15 is returned.
- As a result, transform is called twice for every element that passes through the filter and gets printed.

When calling ++iter, the same happens again:
-- this is trivial now.

Given the following pipeline of transformations t1, t2, t3 and filters f1, f2:
t1 | t2 | f1 | t3 | f2
we have the following behavior:
• For elements where f1 yields false, we call:
t1 t2 f1
• For elements where f1 yields true but f2 yields false, we call:
t1 t2 f1 t1 t2 t3 f2
• For elements where f1 and f2 yield true, we call:
t1 t2 f1 t1 t2 t3 f2 t1 t2 t3

Always take the following into account: avoid expensive transformations before you use a filter.
 */