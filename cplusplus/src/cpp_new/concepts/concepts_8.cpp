/*
 * Support add() function for putting a single or multiple values in a std container (be it vecor, set, deque, map)
 */

#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// concept for narrowing.
template <typename FROM, typename TO>
concept ConvertsWithNarrowing = std::convertible_to<FROM, TO> && // note the use of &&. ConvertsWithNarrowing requires std::convertible_to<> to be satisfied.
                                requires (FROM&& x) {
                                    {std::type_identity_t<TO[]>{std::forward<FROM>(x)}} -> std::same_as<TO[1]>;
                                };

// Concept for push_back
template <typename Coll>
concept PushbackContainer = requires (Coll coll) {
    coll.push_back(std::declval<typename Coll::value_type>());
};

// add for single values
template <typename Coll, typename T>
requires ConvertsWithNarrowing<T, typename Coll::value_type>
void add(Coll& coll, const T& value) {
    if constexpr (PushbackContainer<Coll>) {
        coll.push_back(value);
    } else {
        coll.insert(value);
    }
}

// add for multiple values
template <typename Coll, std::ranges::input_range T>
requires ConvertsWithNarrowing<std::ranges::range_value_t<T>, typename Coll::value_type>
void add(Coll& coll, const T& value) {
    if constexpr (PushbackContainer<Coll>) {
        // vector, deque, list
        coll.insert(coll.end(), std::ranges::begin(value), std::ranges::end(value));
    } else {
        coll.insert(std::ranges::begin(value), std::ranges::end(value));
    }
}

template <typename Coll, typename... Vals>
requires ConvertsWithNarrowing<std::common_type_t<decay_t<decltype(std::forward<Vals>)...>>, typename Coll::value_type>
void add(Coll& coll, Vals&&... values) {
    if constexpr (PushbackContainer<Coll>) {
        // vector, deque, list
        // insert one by one to end of container using push_back
        // will need std::integer_sequence for that
    } else {
        // insert one by one using insert.
        // will need std::integer_sequence for that
    }
}

int main() {
    std::vector<int> iVec;
    add(iVec, 42);

    std::set<int> iSet;
    add(iSet, 42);

    short s = 42;
    add(iVec, s);

    [[maybe_unused]] long long ll = 42;
// add(iVec, ll); // ERROR: narrowing

// add(iVec, 7.7); // ERROR: narrowing
    std::vector<double> dVec;
    add(dVec, 0.7);
    add(dVec, 0.7f);
// add(dVec, 7); // ERROR: narrowing. why is this narrowing?

// insert collections:
    add(iVec, iSet); // OK: insert set elements into a vector
    add(iSet, iVec); // OK: insert vector elements into a set

// can even insert raw array:
    int vals[] = {0, 8, 18};
    add(iVec, vals);

//    add(dVec, vals); // ERROR

    add(dVec, 1, 2, 3, 4, 5); // narrowing
}
