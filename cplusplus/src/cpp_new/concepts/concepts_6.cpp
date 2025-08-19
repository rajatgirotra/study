/*
 * Let's take the same example as concepts_38.cpp, but now we want to support both push_back() and insert() via the add() function.
 * i.e. if collection has insert(), use that, otherwise use push_back() if the collection has push_back()
 *
 * We are only interested in push_back() vs insert() and ignore other requirements like is_copy_constructible and convertible_to
 */

#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;


// First solution, using if constexpr
//template <typename Coll, typename T>
//void add(Coll& coll, const T& value) {
//    // we can use if constexpr (compile time boolean expression) {} else {} as a concept/requires expression also yields
//    // a compile time boolean expression
//    if constexpr (requires (){coll.push_back(value);}) {
//        coll.push_back(value);
//    } else {
//        coll.insert(value);
//    }
//}


// second solution, creating a concept
template <typename Coll>
concept SupportsPushBack = requires (Coll coll) {
    coll.push_back(std::declval<typename Coll::value_type>());
};

// default implementation calls insert
template <typename Coll, typename T>
void add(Coll& coll, const T& value) {
        coll.insert(value);
}

// use a concept for push back which is considered more specialized.
template <SupportsPushBack Coll, typename T>
void add(Coll& coll, const T& value) {
    coll.push_back(value);
}


// third solution, creating a boolean variable template
//template <typename Coll>
//inline constexpr bool SupportsPushBack = requires (Coll coll) {
//    coll.push_back(std::declval<typename Coll::value_type>());
//};
//
//// default implementation calls insert
//template <typename Coll, typename T>
//void add(Coll& coll, const T& value) {
//    coll.insert(value);
//}
//
//// use a concept for push back which is considered more specialized.
//template <typename Coll, typename T>  // template <SupportsPushBack Coll, typename T> is not possible with a variable template
//requires SupportsPushBack<Coll>
//void add(Coll& coll, const T& value) {
//    coll.push_back(value);
//}


int main() {
    std::vector<int> vi;
    add(vi, 100);

    std::set<double> ds;
    add(ds, 100.);

}

// C++20 also provides a new library std::ranges to deal with collections.
// We will look at std::ranges later but std::ranges::input_range is a concept that validates that a collection can be iterated over using begin() and end().
// in concepts_41.cpp we will write a full implementation for add() function to support insert() and push_back() with single or multiple values.
