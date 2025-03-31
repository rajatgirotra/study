/*
 * Views on lvalues usually have reference semantics. this means that usually:
 *    If elements of the referred range are modified, the elements of the view were modified.
 *    If elements of the view are modified, the elements of the referred range were modified.
 *
 * borrowed_iterators: A lot of algorithms in std::ranges namespace which take a range parameter return an iterator as a result.
 * but what if the range parameter is passed as a temporary (prvalue). the returned iterator should not be referenced - otherwise
 * it will cause undefined behavior because the range object is already destroyed after the algorithm is executed.
 * to get around this problem, a number of standard algo's return a borrowed_iterator type.
 *
 * When a standard algo returns a borrowed_iterator type, it means it employs special code to check if its range argument is
 * a prvalue. If yes, it returns a special value std::ranges::dangling. this value can only be copied. Using it (de-referencing it)
 * results in compile time error. Otherwise, if the range argument is lvalue, it is safe to de-reference the returned borrowed_iterator type.
 */
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
#include <random>
#include <iterator>
#include <type_traits>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

auto getData() {
    std::vector v{1,2,3,4,5};
    return v;
}

int main() {

    auto pos = std::ranges::find(getData(), 2);
    static_assert(std::is_same_v<decltype(pos), std::ranges::dangling>);

    // cout << *pos << endl; // error. will not compile, saving you from runtime undefined behavior.

    // the way out is to use lvalue instead to capture the return value from getData(). this extends the lifetime of the temporary.
    auto&& data = getData();
    auto pos2 = std::ranges::find(data, 2);
    if(pos2 != data.end()) {
        cout << "Found: " << *pos2 << endl;
    }

    // Note that borrowed iterators can still dangle if the underlying range object goes out of scope and gets destroyed.
    // This will result in undefined behavior at runtime.
}
