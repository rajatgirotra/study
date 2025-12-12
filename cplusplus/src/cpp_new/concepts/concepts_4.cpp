#include <iostream>
#include <iomanip>
#include <memory>
#include <type_traits>
#include <vector>
#include <set>
#include <atomic>
using namespace std;

// create a template function which takes a Collection and a value and inserts it in the collection using simple push_back().
//template <typename Coll, typename T>
//void add(Coll& coll, const T& value) {
//    coll.push_back(value);
//}
/* what assumptions have we taken about Coll and T here
 * 1) push_back() is available on Coll
 * 2) type T is copy constructible, as push_back() always creates a copy.
 * 3) value is implicitly convertible to the type of elements in Collection
 *
 * We can formalize all that in a concept
 */

template <typename Coll, typename T>
concept SupportsPushBack = requires(Coll c, T v) {
    c.push_back(v);
    std::is_copy_constructible_v<T>;
    requires std::convertible_to<T, typename Coll::value_type>;    // as std::convertible_to is a concept, we need to use the requires clause
    std::is_convertible_v<T, typename Coll::value_type>; // or we can use this instead.
};

template <typename Coll, typename T>
requires SupportsPushBack<Coll, T>
void add(Coll& coll, const T& value) {
    coll.push_back(value);
}
/* since concepts are all evaluated at compile time, there is no runtime cost. The only benefit we get is
 * 1) We get better error msgs/diagnostics from the compiler.
 * 2) We can disable our code for some times which might otherwise work, but doesn't give us the intended behavior.
 */

int main() {
    std::vector<int> vec;
    add(vec, 42);
    // OK
    add(vec, "hello"); // ERROR: no conversion from string literal to int

    std::set<int> coll;
    add(coll, 42); // ERROR: no push_back() supported by std::set<>

    std::vector<std::atomic<int>> aiVec;
    std::atomic<int> ai{42};
    add(aiVec, ai); // ERROR: cannot copy/move atomics
}
