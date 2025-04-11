/*
 * borrowed_ranges: A borrowed range is a range whose iterators are still valid and can be de-referenced even after the range
 * they refer to no longer exists.
 *
 * this can happen,
 * 1) if the iterators of the range are independent of the lifetime of the underlying range.
 * 2) or if the iterators themselves store the values which need to be iterated upon.
 *
 * C++20 introduces a concept rng::borrowed_range which is satisfied if the iterators can still be used when the underlying range
 * no longer exists.
 *
 * the concept of a borrowed range was introduced to allow ranges to work safely with temporaries.
 *
 * Ranges often return iterators that refer to data inside the range object. If the range is a temporary, and it gets destroyed after
 * passing it to an algorithm, then those iterators become dangling — unless the range is a borrowed_range.
 *
 * now the ranges which you have seen till now are:
 * 1) STL containers: These are obviously NOT borrowed ranges as their iterators refer to values stored in them.
 * 2) views: constructed using range adaptor function. any view created by passing a range object to the range adaptor functions
 *    as prvalue (a temporary); will again NOT be borrowed ranges.
 *
 * So which views can be borrowed ranges.
 *
 * 1) rng::iota_view --> in this view, the iterator itself stores the current value to be used and incremented.
 * 2) rng::empty_view --> in this view, the iterator always points to the end iterator so there are no elements to be traversed.
 * 3) views where the iterators directly refer to the underlying range on which the view is constructed. This is the case with
 *    3.a) std::string_view
 *    3.b) rng::ref_view
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
    std::vector coll{0, 8, 15}; // coll is not a borrowed range
    auto pos0 = rng::find(coll, 8);
    std::cout << "Pos0: " <<  *pos0 << endl;

    // take returns a take_view<ref_view<...>>, take_view<> is a borrowed range, as it has an underlying_view.
    auto rg_first_2 = vws::take(coll, 2);
    auto pos1 = rng::find(rg_first_2, 8);
    cout << "Pos1: " << *pos1 << endl;

    [[maybe_unused]] auto  pos2 = rng::find(std::vector{8}, 8); // argument is rvalue, so return type if rng::danling.
    // std::cout << *pos2 << endl;

    [[maybe_unused]] auto pos3 = rng::find(vws::single(8), 8); // yields dangling
    // std::cout << *pos3 << endl;

    // iota_view is a borrowed range
    [[maybe_unused]] auto pos4 = std::ranges::find(std::views::iota(8), 8);
    // borrowed range
    std::cout << "Pos4: " << *pos4 << endl;

    [[maybe_unused]] auto pos5 = std::ranges::find(std::views::empty<int>, 8); // borrowed range
    // std::cout << "Pos5: " << *pos5 << endl; // can dereference an iterator of an empty<> range.

    //auto counted_view = std::views::counted(std::vector{0, 8, 15}.begin(), 2);
    // views created by counted() adaptor are borrowed ranges. Why? Read the description at the end.
    [[maybe_unused]] auto pos6 = std::ranges::find(std::views::counted(std::vector{0, 8, 15}.begin(), 2),8);
    // std::cout << "Pos5: " << *pos5 << endl; // although counted() returns a borrowed_range, if the underlying range itself is a temporary, like std::vector{0, 8, 15} here
    // the iterator will be invalid after the function call the temporary will be destroyed.

    auto v = vws::take(std::vector{0, 8, 15}, 2);
    auto pos7 = rng::find(v, 8);
    cout << "Pos7: " << *pos7 << endl;
    cout << "type of v: " << demangle(typeid(decltype(v)).name()) << endl; // not a ref_view, an owning_view

     auto pos8 = rng::find(vws::counted(std::vector{0, 8, 15}.begin(), 2), 8);
    // auto v2 = vws::counted(std::vector{0, 8, 15}.begin(), 2);
    // auto pos8 = rng::find(v2, 8);
    std::cout << "Pos8: " << *pos8 << endl;  // runtime ERROR even if 8 found
    // cout << "type of v2: " << demangle(typeid(decltype(v2)).name()) << endl; // v2 is std::span

    // [[maybe_unused]] auto pos9 = rng::find(std::vector{0, 8, 15}, 8);
    // cout << *pos9 << endl; // dangling pointer rng::dangling

    // [[maybe_unused]] auto pos5 = rng::find(vws::take(std::vector{0, 8, 15}, 2), 8);
    // cout << *pos5 << endl;
}

/* For continuing studying ranges and views, start at ranges_and_views_75.cpp
 *
 * auto r = std::views::counted(ptr, n);
 * This creates a range that starts at pointer ptr and spans n elements. It's implemented as std::ranges::subrange<It>, where It is a counted iterator type.
 * Importantly: The range does not own the data — it just views n elements starting at ptr.
 *
 * Why is it a borrowed_range?
 * Because the range does not manage any storage, and the iterators just hold a copy of the original pointer (ptr), the lifetime of the underlying data is independent of the range object.
 * So even if the range is a temporary:
 * std::ranges::for_each(std::views::counted(ptr, n), ...);
 * …it’s still safe, as the iterators don’t depend on the lifetime of the view object itself, just on ptr being valid.
 * That makes it safe for the range to be a temporary — hence, std::views::counted returns a borrowed_range.
 *
 * However, if the argument to std::counted(...) is a prvalue, it will be destroyed at the end of the expression and the iterator to it will be invalid.
 */