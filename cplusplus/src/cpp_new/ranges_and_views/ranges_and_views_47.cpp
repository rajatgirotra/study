#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <cxxabi.h>
#include <cassert>
#include <tuple>
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
    std::vector intVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    // create a view of only the first 5 elements of intVec.
    auto v = vws::take(intVec, 5);
//    auto v = vws::counted(intVec.begin(), 5);
    rng::copy(v, std::ostream_iterator<int>(cout, "  "));
    cout << endl;
    cout << "\ntype of view returned by vws::take(..):  " << demangle(typeid(decltype(v)).name()) << endl;
    /* Type of take view: std::ranges::take_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > > > */

    // create a view from intVec where elements are divisible by 3.
    auto v1 = vws::filter(intVec, [](const auto &elem) { return elem % 3 == 0; });
    rng::copy(v1, std::ostream_iterator<int>(cout, "  "));
    cout << endl;
    cout << "\ntype of view returned by vws::filter(..):  " << demangle(typeid(decltype(v1)).name()) << endl;
    /* Type of filter view: std::ranges::filter_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > >, main::{lambda(auto:1&&)#1}> */

    // transform the view by squaring all elements
    auto v2 = vws::transform(intVec, [](const auto &elem) { return elem * elem; });
//    auto v2 = vws::transform(intVec, [](auto &elem) { return (elem *= elem); });
    std::ranges::copy(v2, std::ostream_iterator<int>(cout, "  "));
    cout << "\ntype of view returned by vws::transform(..):  " << demangle(typeid(decltype(v2)).name()) << endl;
    cout << endl;
    /* Type of transform view: std::ranges::transform_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > >, main::{lambda(auto:1&)#1}> */

    // did transform modify original intVec, answer is it depends. Normally when adaptor functions are called with range parameter as lvalue, you get a reference_view.
    // reference_views can be used for both reading/writing. However, when adaptor functions are called with rvalue/temporaries, we don't get a reference_view.
    // so reading is ok, but not writing.
    cout << "Original collection: ";
    std::ranges::copy(intVec, std::ostream_iterator<int>(cout, "  "));
    cout << endl;

    const std::vector<std::tuple<int, char, std::string>> vt {
        {1, 'A', "α"},
        {2, 'B', "β"},
        {3, 'C', "γ"},
        {4, 'D', "δ"},
        {5, 'E', "ε"},
    };

    auto&& element_0_view = vws::elements<0>(vt);
    cout << "element<0> view: ";
    rng::copy(element_0_view, std::ostream_iterator<int>(cout, "  "));
    /*
     * Type of elements view: std::ranges::elements_view<std::ranges::owning_view<std::vector<std::tuple<int, char, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::tuple<int, char, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >, 1ul>
     * If range is passed as rvalue, otherwise it will be std::ranges::ref_view.
     * or
     * Type of elements view: std::ranges::elements_view<std::ranges::ref_view<std::vector<std::tuple<int, char, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::tuple<int, char, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >, 1ul>
     */

    auto&& element_1_view = vws::elements<1>(vt);
    cout << "\nelement<1> view: ";
    rng::copy(element_1_view, std::ostream_iterator<char>(cout, "  "));

    auto&& element_2_view = vws::elements<2>(vt);
    cout << "\nelement<2> view: ";
    rng::copy(element_2_view, std::ostream_iterator<string>(cout, "  "));

    cout << endl;
    // views can be nested. create a view of only elements that are divisible by 3. square them and choose only the first 2.
    auto final_view = vws::take(vws::transform(vws::filter(intVec, [](const auto &elem) {
        return elem % 3 == 0;
    }), [](const auto &elem) {
        return elem * elem;
    }), 2);
    rng::copy(final_view, std::ostream_iterator<int>(cout, "  "));
    cout << endl;

    /*
     * Type of nested view: std::ranges::take_view<std::ranges::transform_view<std::ranges::filter_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > >, main::{lambda(auto:1 const&)#1}>, main::{lambda(auto:1&)#2}> >
     */


    // the above nesting can get really tedious. So view class overload the pipe operator |, to make this nesting easier to code and understand.

    auto final_view_2 = intVec
                        | vws::filter([](const auto &elem) { return elem % 3 == 0; })
                        | vws::transform([](const auto &elem) { return elem * elem; })
                        | vws::take(2);
    std::ranges::copy(final_view_2, std::ostream_iterator<int>(cout, "  "));
    cout << endl;
}