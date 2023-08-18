#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>
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
    std::vector intVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    // create a view of only the first 5 elements of intVec.
    auto v = vws::take(intVec, 5);
//    auto v = vws::counted(intVec.begin(), 5);
    std::ranges::copy(v, std::ostream_iterator<int>(cout, "  "));
    cout << endl;

    // create a view from intVec where elements are divisible by 3.
    auto v1 = vws::filter(intVec, [](const auto &elem) { return elem % 3 == 0; });
    std::ranges::copy(v1, std::ostream_iterator<int>(cout, "  "));
    cout << endl;

    // transform the view by squaring all elements
    auto v2 = vws::transform(intVec, [](const auto &elem) { return elem * elem; });
//    auto v2 = vws::transform(intVec, [](auto &elem) { return (elem *= elem); });
    std::ranges::copy(v2, std::ostream_iterator<int>(cout, "  "));
    cout << "\ntype of view returned by vws::filter(..):  " << demangle(typeid(decltype(v)).name()) << endl;
    cout << endl;

    // did transform modify original intVec, answer is it depends. Normally when adaptor functions are called with range parameter as an lvalue, you get a reference_view.
    // reference_views can be used for both reading/writing. However, when adaptor functions are called with rvalue/temporaries, we don't get a reference_view.
    // so reading is ok, but not writing.
    cout << "Original collection: ";
    std::ranges::copy(intVec, std::ostream_iterator<int>(cout, "  "));
    cout << endl;

    // views can be nested. create a view of only elements that are divisible by 3. square them and choose only the first 2.
    auto final_view = vws::take(vws::transform(vws::filter(intVec, [](const auto &elem) {
        return elem % 3 == 0;
    }), [](const auto &elem) {
        return elem * elem;
    }), 2);
    std::ranges::copy(final_view, std::ostream_iterator<int>(cout, "  "));
    cout << endl;

    // the above nesting can get really tedious. So view class overload the pipe operator |, to make this nesting easier to code and understand.

    auto final_view_2 = intVec
                        | vws::filter([](const auto &elem) { return elem % 3 == 0; })
                        | vws::transform([](const auto &elem) { return elem * elem; })
                        | vws::take(2);
    std::ranges::copy(final_view_2, std::ostream_iterator<int>(cout, "  "));
    cout << endl;
}