/*
 * You can actually create the views directly instead of using range adaptors. But it is not recommended. That's because
 * range adaptors are carefully written, they always work and sometimes may also apply some optimizations.
 *
 * Also, most views on lvalues (i.e. where the range parameter has a name) have reference semantics. This means that the underlying
 * range and iterators must be valid when the view is used. Also, if there are any changes to the range during the time that the view and is
 * created and when it is used, you might get unexpected results. That's why it is always recommended to create views right at the time when
 * you need them.
 */
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <string>
#include <cxxabi.h>
#include <typeinfo>
#include <cassert>
using namespace std;
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
    std::vector intVec {10, -99, 67, 0, 567};
    auto v = intVec | vws::take(3);
    cout << "type of v: " << demangle(typeid(decltype(v)).name()) << endl;
    //std::ranges::take_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > > >
    // you can see from the type itself, that take_view uses std::ranges::ref_view to reference the underlying range.

    // since this a reference view, it can be used for both reading and writing. Let's sort the range using a view.
    std::ranges::sort(intVec | vws::take(intVec.size()));
    std::ranges::copy(intVec, std::ostream_iterator<int>(cout, "  "));
}