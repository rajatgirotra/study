/*
 * Some more example of borrowed_iterator and borrowed_range.
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

auto getData() {
    return std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}

int main() {
    std::vector coll{0, 8, 15}; // coll is not a borrowed range
    auto pos0 = rng::find(coll, 8); // coll is lvalue, so pos0 is valid iterator
    std::cout << "Pos0: " <<  *pos0 << endl;

    std::vector<int> intVec {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int>::iterator pos1{};
    {
        auto rg_first_2 = vws::take(intVec, 7);
        pos1 = rng::find(rg_first_2, 5); // rg_first_2 is lvalue, so pos1 is valid iterator.
    }
    // rg_first_2 is destroyed here, but no issues, as intVec still lives so iterator will be valid.
    cout << "value (pos1): " << *pos1 << " found at index " << std::distance(begin(intVec), pos1) << endl;

    std::vector<int>::iterator pos2{};
    {
        // std::vector<int> is not a borrowed range.
        auto rg_first_2 = vws::take(getData(), 7);
        // The resulting take_view<vector<int>> wraps a temporary non-borrowed range. But the lifetime of the temporary is now extended.
        pos2 = rng::find(rg_first_2, 5); // since the lifetime of the temporary returned by getData() is extended, pos2 ia valid.
    }
    // now rg_first_2 goes out of scope and so does the temporary. So dereferencing pos2 is now undefined behavior. May or may not work.
    cout << "value (pos2): " << *pos2 << " found at index \n";

    [[maybe_unused]] auto  pos3 = rng::find(std::vector{8}, 8); // argument is rvalue, so return type if rng::danling.
    // std::cout << *pos3 << endl;

    // vws::single(8) returns a view of only the one element passed as argument. It just holds the element inside the view itself.
    // so again it is NOT A borrowed range.
    [[maybe_unused]] auto pos4 = rng::find(vws::single(8), 8); // yields dangling
    // std::cout << *pos4 << endl;

    // iota_view is a borrowed range
    [[maybe_unused]] auto pos5 = std::ranges::find(std::views::iota(8), 8);
    // borrowed range
    std::cout << "Pos5: " << *pos5 << endl;

    [[maybe_unused]] auto pos6 = std::ranges::find(std::views::empty<int>, 8); // borrowed range
    std::cout << "Pos6: " << *pos6 << endl; // can dereference an iterator of an empty<> range.

    auto counted_view = std::views::counted(std::vector{0, 8, 15}.begin(), 2);
    // views created by counted() adaptor are borrowed ranges. Why? Read the description at the end.
    // counted() doesnt take a range, it takes an iterator as argument and a count of number of elements in the view.
    [[maybe_unused]] auto pos7 = std::ranges::find(std::views::counted(std::vector{0, 8, 15}.begin(), 2),8);
    std::cout << "Pos7: " << *pos7 << endl; // although counted() returns a borrowed_range, if the underlying range itself is a temporary, like std::vector{0, 8, 15} here
    // the iterator will be invalid after the function call the temporary will be destroyed.
    // so even though pos7 may print correct value, it is actually undefined behavior.

    auto v = vws::take(std::vector{0, 8, 15}, 2);
    auto pos8 = rng::find(v, 8);
    cout << "Pos8: " << *pos8 << endl;
    cout << "type of v: " << demangle(typeid(decltype(v)).name()) << endl; // all this is ok. v is an lvalue so lifetime of vector is extended.

    auto pos9 = rng::find(vws::counted(std::vector{0, 8, 15}.begin(), 2), 8);
    std::cout << "Pos9: " << *pos8 << endl;  // runtime ERROR even if 8 found
    // auto v2 = vws::counted(std::vector{0, 8, 15}.begin(), 2);
    // auto pos9 = rng::find(v2, 8);
    // cout << "type of v2: " << demangle(typeid(decltype(v2)).name()) << endl; // v2 is std::span

    [[maybe_unused]] auto pos10 = rng::find(std::vector{0, 8, 15}, 8);
    // cout << *pos10 << endl; // pos10 will be rng::dangling

    [[maybe_unused]] auto pos11 = rng::find(vws::take(std::vector{0, 8, 15}, 2), 8);
    // cout << *pos11 << endl; // pos11 will be dangling
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