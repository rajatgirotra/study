/*
 * borrowed_ranges: A borrowed range is a range whose iterators are still valid and can be de-referenced even after the range
 * they refer to no longer exists.
 *
 * this can happen,
 * 1) if the iterators of the range are independent of the lifetime of the underlying range.
 * 2) or if the iterators themselves store the values which need to be iterated upon.
 *
 * C++20 introduces a concept std::ranges::borrowed_range which is satisfied if the iterators can still be used when the underlying range
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
 * 3) views where the iterators directly refer to the underlying range on which the view is constructed. This is the case with
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
#include <cxxabi.h>
#include <cassert>
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
//    auto v = std::views::take(std::vector{0, 8, 15}, 2);
//    auto pos8 = rng::find(v, 8);
//    cout << *pos8 << endl;
//    cout << "type of v: " << demangle(typeid(decltype(v)).name()) << endl; // not a ref_view, an owning_view

    //    auto pos8 = rng::find(vws::counted(std::vector{0, 8, 15}.begin(), 2), 8);
//    auto v2 = vws::counted(std::vector{0, 8, 15}.begin(), 2);
//    auto pos8 = rng::find(v2, 8);
//    std::cout << *pos8 << endl;  // runtime ERROR even if 8 found
//    cout << "type of v2: " << demangle(typeid(decltype(v2)).name()) << endl; // v2 is std::span

//    auto pos8 = rng::find(std::vector{0, 8, 15}, 8);
//    cout << *pos8 << endl; // dangling pointer std::ranges::dangling

    [[maybe_unused]] auto pos5 = std::ranges::find(std::views::take(std::vector{0, 8, 15}, 2), 8);
}