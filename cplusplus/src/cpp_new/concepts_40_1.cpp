/*
 * Let's look at some expressions we can put inside a requires expression.
 */

#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <bit>
#include <memory>
using namespace std;


template<typename Coll, typename T, typename U>
concept ExampleConcept = requires(Coll coll, T t, U u, Coll::value_type v)
{
    // can only check for names in Coll which are defined using "typedef" or "using" keywords.
    typename Coll::value_type::first_type;
    // Coll must have embedded value_type::first_type, i.e. it should be well defined.
    typename Coll::value_type::second_type; // Coll must have embedded value_type::second_type

    t + u; // t + u must be defined.
    t - u; // t - u must be defined.

    cout << v; // makes sure Coll::value_type has operator << defined.

    true; // dummy clause to make the requires expression pass as the requires expression cannot be empty.

    *t; // t is dereferencable
    t->value(); // -> is overloaded for T.
    u[0]; // [] operator is overloaded in U.
    u == nullptr; // type U can be compared to nullptr;
    *t > u; // *t type can be compared with type U

    requires std::integral<U>; // U must be integral type.
};

// Do define if *t is allowed OR type U can be compared to nullptr, you CAN'T DO:
template<typename Coll, typename T, typename U>
concept ExampleConcept2 = requires(Coll coll, T t, U u, Coll::value_type v)
{
    *t || u == nullptr;
    // this only means that result of *t and result of u==nullptr can be combined together with the || operator.
    // if you really want one of these to be true, you have to write two requires expressions.
};

template<typename Coll, typename T, typename U>
concept ExampleConcept3 = requires(Coll coll, T t, U u, Coll::value_type v)
                          {
                              *t;
                          } || requires(Coll coll, T t, U u, Coll::value_type v) { u == nullptr; };

template<typename Coll, typename T, typename U>
concept ExampleConcept4 = std::integral<U> && requires(Coll coll, T t, U u, Coll::value_type v)
{
    true;
};


template<typename T1, typename T2>
concept ExampleConcept5 = requires
{
    typename T1::value_type; // type member value_type required for T1
    typename std::ranges::iterator_t<T1>; // iterator type required for T1
    typename std::common_type_t<T1, T2>; // T1 and T2 have to have a common type
};

class Dummy {
};

namespace std {
    template<>
    class hash<Dummy> {
    public:
        size_t operator()(const Dummy &) const { return 0; }
    };
}

template<typename T>
concept StdHashExistsInvalid = requires(T t)
{
    typename std::hash<T>;
};

template<typename T>
concept StdHashExistsValid = requires(T t)
{
    std::hash<T>{};
};


template<StdHashExistsInvalid T>
class HasHashInvalid {
};

template<StdHashExistsValid T>
class HasHashValid {
};

/*
 *as you would have seen already,
 * template <typename T>
 * concept ...  = requires (T x) {
 *    {x == x}; // implies x can be compared to itself.
 *    {x == x} -> std::convertible_to<bool>; // implies that the result of x==x can be converted to bool
 *    {x == x} noexcept; // means that the comparison function does not throw.
 *    {x == x} noexcept -> std::convertible_to<bool>; // can combine noexcept with ->
 *    {&x} -> std::bidirectional_iterator; // means that decltype(&x) is a bidirectional iterator type.
 * };
 */

// write a concept that has to ensure that both the operator * and the operator [] yield the same type for a given type.
template<typename T>
concept DerefAndIndexMatch = requires(T t)
{
    requires std::same_as<decltype(*t), decltype(t[0])>;
};

// or
template<typename T>
concept DerefAndIndexMatch2 = std::same_as<decltype(*declval<T>()), decltype(declval<T>()[0])>;

class DerefAndIndexTest {
public:
    int m_data[10]{};
    int operator*() { return m_data[0]; }
    int operator[](int) { return m_data[0]; }
    //int &operator[](int) { return m_data[0]; }
};

template<DerefAndIndexMatch T>
class DeferTest1 {
};

template<DerefAndIndexMatch2 T>
class DeferTest2 {
};

// Concepts can also be applied to non-type template parameters (NTTP). For example:
template<auto Val>
concept LessThan10 = Val < 10;

template<int Val>
requires LessThan10<Val>
class MyValueType {};

// write a concept which only accepts power of 2 as argument. So it uses a Non Type Template Parameter.
template <auto Val>
concept PowerOf2 = std::has_single_bit(static_cast<size_t>(Val)); // std C++ function to tell if argument is power of 2.

template <auto Val>
requires PowerOf2<Val>
class Memory {};

// More examples.
template<std::convertible_to<int> T>
class MyClass {};

auto myFunc(const std::convertible_to<int> auto& val) {}; // decltype(val) must be convertible to int

template<typename T>
concept MyConcept = requires(T x) {
    { x + x } -> std::convertible_to<int>; // decltype(x+x) must be convertible to int.
};

// std::invocable is a concept that constraints a Callable's arguments.
template<std::invocable<int, std::string> Callable>
void call(Callable op); // Callable should take an int and string.

void call(std::invocable<int, std::string> auto op); // Callable should take an int and string.

double f() { return 0; }
std::floating_point auto val1 = f(); // concept on a simple variable.

std::copyable auto foo(auto) {
    return std::make_unique<int>(10); // will fail constraint checking as unique_ptr is not copyable.
}

int main() {
    [[maybe_unused]] HasHashInvalid<Dummy> h1;
    // why this succeeds. because StdHashExists only makes sure that type "std::hash<T>" is valid for T. which will be true for all T.
    //to really make sure we have std::hash<> overriden for T, we must try to create an object of std::hash<> type.

    [[maybe_unused]] HasHashValid<Dummy> h2;

    // [[maybe_unused]] DeferTest1<DerefAndIndexTest> dt1;
    [[maybe_unused]] DeferTest2<DerefAndIndexTest> dt1;

    [[maybe_unused]] MyValueType<9> mvt;

    Memory<1> m1;
    Memory<2> m2;
    // Memory<3> m3;
    Memory<4> m4;
    // Memory<5> m5;
    // Memory<6> m6;
    // Memory<7> m7;
    Memory<8> m8;

    auto x = foo(100);
}
