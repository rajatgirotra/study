/*
 * Write myMin<T>(a, b) without using any std facilities. Add a constraint that T must be less-than-comparable
 * using a static_assert.
 *
 * Hint:
 * decltype + void : decltype(expr) gives you the type of an expression without evaluating it.
 * If the expression is invalid, the whole specialisation is discarded (SFINAE).
 *
 * Note that in edge cases type of a and b could be different
 */

#include <type_traits>
#include <utility>
#include <iostream>


namespace without_concepts
{
    template <typename T, typename U=T, typename = void>  struct is_less_comparable : std::false_type {};

    template <typename T, typename U>
    struct is_less_comparable<T, U, std::void_t<decltype(std::declval<T>() < std::declval<U>())>> : std::true_type {};

    template <typename T, typename U=T>
    inline constexpr bool is_less_comparable_v = is_less_comparable<T, U>::value;


}

namespace with_concepts
{
    template <typename T, typename U=T>
    concept is_less_comparable = requires(T a, U b)
    {
        {a < b} -> std::convertible_to<bool>;
    };

    template <typename T, typename U=T>
    inline constexpr bool is_less_comparable_v = is_less_comparable<T, U>;
}

namespace
{
    template <typename T, typename U>
     std::common_type_t<T, U> myMin(T&& a, U&& b)
    {
        static_assert(without_concepts::is_less_comparable_v<T, U>, "types must be less than comparable");
        static_assert(with_concepts::is_less_comparable_v<T, U>, "types must be less than comparable");
        return b < a ? std::forward<U>(b) : std::forward<T>(a);
    }
}

struct NotComparable {
    int x;
    // deliberately no operator
};

struct CustomComparable {
    int x;
    bool operator<(const CustomComparable& o) const { return x < o.x; }
};

using namespace without_concepts;

int main() {
    // These compile and work
    std::cout << myMin(3, 7)         << "\n";   // 3
    std::cout << myMin(3.14, 2.72)   << "\n";   // 2.72
    std::cout << myMin('z', 'a')     << "\n";   // a
    std::cout << myMin(1.0f, -1.0f)  << "\n";   // -1
    std::cout << myMin(-100, -1.0f)  << "\n";   // -100

    CustomComparable p{5}, q{3};
    std::cout << myMin(p, q).x       << "\n";   // 3

    // This fails to compile with our message:
    // NotComparable u{1}, v{2};
    // myMin(u, v);
    // error: static assertion failed: myMin requires T to support operator

    // Verify the trait itself
    static_assert( without_concepts::is_less_comparable_v<int>);
    static_assert( without_concepts::is_less_comparable<int>::value);
    static_assert( without_concepts::is_less_comparable_v<double>);
    static_assert( without_concepts::is_less_comparable_v<CustomComparable>);
    static_assert(!without_concepts::is_less_comparable_v<NotComparable>);

    // Verify the trait itself where types are different
    static_assert( without_concepts::is_less_comparable_v<int, double>);
    static_assert( without_concepts::is_less_comparable_v<double, char>);
    static_assert( without_concepts::is_less_comparable_v<unsigned int, long>);

    // verify using concepts
    static_assert( with_concepts::is_less_comparable_v<int>);
    static_assert( with_concepts::is_less_comparable_v<double>);
    static_assert( with_concepts::is_less_comparable_v<CustomComparable>);
    static_assert(!with_concepts::is_less_comparable_v<NotComparable>);

    static_assert( with_concepts::is_less_comparable_v<int, double>);
    static_assert( with_concepts::is_less_comparable_v<double, char>);
    static_assert( with_concepts::is_less_comparable_v<unsigned int, long>);
}