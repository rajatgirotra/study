#include <iostream>
#include <vector>
#include <ranges>
namespace vws = std::views;
/*
 * views are lazily evaluated. If you see the output you will know.
 * each item goes through the chain of range adaptor functions and when processing completes, the next item is processed.
 */

int main()
{
    std::vector<int> coll{ 8, 15, 7, 0, 9 };
    // define a view:
    auto vColl = coll
    | vws::filter([] (int i) {
         std::cout << " filter " << i << '\n';
        return i % 3 == 0;})
    | vws::transform([] (int i) {
        std::cout << " trans " << i << '\n';
        return -i;
       });

    // and use it:
    std::cout << "*** coll | filter | transform:\n";
    for (int val : vColl) {
        std::cout << "val: " << val << "\n\n";
    }
}
