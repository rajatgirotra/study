/*
 * borrowed_ranges: A borrowed range is a range whose iterators are still valid and can be de-referenced even after the range
 * they refer to no longer exists.
 *
 * this can happen,
 * 1) if they iterators of the range are independent of the lifetime of the underlying range.
 * 2) or if the iterators themselves store the values which need to be iterated upon.
 *
 * C++20 introduces a concept std::ranges::borrows_range which is satisfied if the iterators can still be used when the underlying range
 * no longer exists.
 *
 * now the ranges which you have seen till now are:
 * 1) STL containers: These are obviously NOT borrowed ranges as their iterators refer to values stored in them.
 * 2) views: constructed using range adaptor function. any view created by passing a range object to the range adaptor functions
 *    as prvalue (a temporary); will again NOT be borrowed ranges.
 *
 * So which views can be borrowed ranges.
 *
 * 1) std::ranges::iota_view --> in this view, the iterator itself stores the current value to be used and incremented.
 * 2) std::ranges::empty_view --> in this view, the iterator always points to the end iterator so there are no elements to be traversed.
 * 3) views where the iterators directly refer to the underlying range on which the view is contructed. This is the case with
 *    3.a) std::string_view
 *    3.b) std::ranges::ref_view
 *    3.c) std::span
 *    3.d) std::ranges:subrange
 *
 * Note that some range adaptor functions already check if their range parameter is prvalue. If yes, the invocation results
 * in compile time error. some range adaptors don't check for prvalues and rely on programmers.
 */
#include <iostream>
#include <concepts>
#include <ranges>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

int main() {
//    auto v = std::views::take(std::vector{0, 8, 15}, 2); // this is a compile time error.

    auto pos6 = rng::find(vws::counted(std::vector{0, 8, 15}.begin(), 2), 8);
    std::cout << *pos6 << endl;  // runtime ERROR even if 8 found
}