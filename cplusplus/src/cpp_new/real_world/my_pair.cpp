/*
 * Implement your own Pair<T, U> with first/second members and a make_pair helper.
 * Practice passing two independent type params
 */

#include <iostream>
#include <vector>
using namespace std;

namespace my
{
    template <typename T, typename U>
    struct pair
    {
        using first_type = T;
        using second_type = U;

        first_type first{};
        second_type second{};

        pair() = default;

        template <typename X, typename Y>
        pair(X&& x, Y&& y) : first(std::forward<X>(x)), second(std::forward<Y>(y))
        {
        }

        void swap(pair<first_type, second_type>& rhs) noexcept (
            std::is_nothrow_swappable_v<T> && std::is_nothrow_swappable_v<U>)
        {
            std::swap(first, rhs.first);
            std::swap(second, rhs.second);
        }

        // comparison, so my::pair can be used in maps, sets, etc
        auto operator<=>(const pair<T, U>&) const = default;
    };

    template <typename X, typename Y>
    auto make_pair(X&& x, Y&& y)
    {
        using decayed_pair = pair<std::decay_t<X>, std::decay_t<Y>>; // will remove any references and cv qualifiers.
        return decayed_pair(x, y);
    }

    template <typename T, typename U>
    ostream& operator<<(ostream& os, const pair<T, U> p) noexcept
    {
        os << "Pair (" << p.first << ", " << p.second << ")";
        return os;
    }
}

int main()
{
    my::pair<int, double> p1{};
    cout << p1 << endl;

    auto p2 = my::make_pair(10, 20.);
    cout << p2 << endl;

}