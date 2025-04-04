/*
 * till now the only range you have seen is an array or an STL container class which has a begin() and end() iterators
 *
 * But those are not the only range objects. You can also create range objects based on
 * 1) a begin() iterator and a sentinel
 * 2) a begin() iterator and a count.
 *
 * But how do we really create those ranges?? using rng::subrange<>
 * rng::subrange<> is a helper class which can create view objects for you (which are valid range objects).
 * All you have to do to create a subrange is to pass a begin() iterator and sentinel to it.
 */
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

template<auto End>
struct EndValue {
    bool operator== (auto pos) const noexcept {
        return *pos == End; // end is where iterator points to End
    }
};

int main()
{
    std::vector coll = {42, 8, 0, 15, 7, -1};
// define a range referring to coll with the value 7 as end:
    rng::subrange range{coll.begin(), EndValue<7>{}}; // i.e. 42, 8, 0, 15
// sort the elements of this range:
    rng::sort(range);
// print the elements of the range:
    rng::for_each(range,
                          [] (auto val) {
                              std::cout << ' ' << val;
                          });
    std::cout << '\n';
// print all elements of coll up to -1:
    rng::for_each(coll.begin(), EndValue<-1>{},
                          [] (auto val) {
                              std::cout << ' ' << val;
                          });
    std::cout << '\n';
}
