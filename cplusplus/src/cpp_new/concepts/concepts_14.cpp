/* starting from concepts_14.cpp, we are not discussing new things. We are just practicing what we have learnt */

#include <iostream>
#include <concepts>
#include <type_traits>
#include <utility>
#include <format>
#include <string>
#include <string_view>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <ranges>
using namespace std;

namespace rng = std::ranges;
namespace vws = std::views;

template <typename Coll, typename T>
concept SupportsPushBack = requires (Coll&& coll, T&& val)
{
    // T must be copy constructible
    std::is_copy_constructible_v<std::remove_cvref_t<T>>;

    // T must be implicitly convertable to Coll::value_type
    requires std::convertible_to<std::remove_cvref_t<T>, typename std::remove_cvref_t<Coll>::value_type>;

    // coll.push_back(v) must be well formed
    std::forward<Coll>(coll).push_back(std::forward<T>(val));
};

template <typename Coll, typename T>
requires SupportsPushBack<Coll, T>
void add(Coll&& coll, T&& val) {
    std::forward<Coll>(coll).push_back(std::forward<T>(val));
}

template <typename FROM, typename TO>
concept ConvertsWithoutNarrowing = std::convertible_to<FROM, TO> &&
    requires (FROM&& from) {
    {std::type_identity_t<TO[]>{std::forward<FROM>(from)}} -> std::same_as<TO[1]>;
};


template <typename Coll>
requires requires (Coll coll) {
    typename Coll::value_type;
}
ostream& operator << (ostream& os, const Coll& coll) {
    cout << "collection: ";
    rng::copy(coll, ostream_iterator<typename Coll::value_type>(os, ", "));
    return os;
}

int main() {
    std::vector<int> v;
    add(v, 6);
    add(v, 6.6); // how do you prevent add without narrowing

    cout << v << endl;
}