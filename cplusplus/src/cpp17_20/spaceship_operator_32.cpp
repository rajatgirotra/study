/*
 * If you want to allow your user defined class objects to be compared for equality and comparison, you need to overload 6 operations.
 *
 * // equality
 * bool operator == (const MyType& rhs);
 * bool operator != (const MyType& rhs); // can use operator ==
 *
 * // comparison (relational operators)
 * bool operator < (const MyType& rhs);
 * bool operator <= (const MyType& rhs); // can use operator <
 * bool operator > (const MyType& rhs); // can use operator <
 * bool operator >= (const MyType& rhs); // can use operator >=
 *
 * So basically you only need to implement == and < operators. All others can reuse these two.
 * Since this is a lot of boilerplate, C++20 made two changes.
 *
 * 1) Since C++20, operator == implies !=. I.e. if you have overloaded ==, you don't need to overload !=.
 *    As for a != b, the compiler will try 1) a != b, 2) !(a==b), 3) !(b==a) in that order.
 *    a and b doesn't necessarily be the same types. They can be different types.
 *
 * 2) Since C++20, a new operator <=> is introduced, which can performs comparisons <, <=, >, >=. this spaceship operator doesn't return a boolean.
 *    it performs a three-way comparison, which yields a value you can compare with 0. So if you do.
 *    if x <=> y == 0, then x == y
 *    if x <=> y < 0, then x < y
 *    if x <=> y > 0, then x > y
 *    So x <= y, it might be re-written as (x <=> y) <= 0, or (y <=> x) >= 0
 *
 *    need to #include <compare> header.
 *    Further more in 1) if for a!=b, the compiler tries !(b==a), it is possible that an implicit type conversion of the first parameter "a" might take place,
 *    as it becomes a parameter in the !(b==a) call. Given that MyTypeB operator == (const MyTypeA& a) is defined.
 *
 *    Also, the standard says that if you use the default <=> operator in your class, it will implicitly insert an equality operator for you. Example:
 *
 *    class Value {
 *       int m_val;
 *    public:
 *       auto operator <=> (const Value& rhs) const = default;
 *       auto operator == (const Value& rhs) const = default; // implicitly generated.
 *    };
 *    So just by declaring the default spaceship operator, you get all 6 comparison operator. If you instead have your own implementation of spaceship operator, then you
 *    must define the == operator also.
 *
 *    class Value {
 *       int m_val;
 *    public:
 *       auto operator <=> (const Value& rhs) const noexcept {
 *           return this->m_val <=> rhs.m_val; // defines ordering (<, >, <=, >=)
 *       }
 *       bool operator == (const Value& rhs) const noexcept {
 *           return this->m_val == rhs.m_val; // defines equality (== and !=)
 *       }
 *    };

 */


#include <iostream>
#include <iomanip>
#include <compare>
using namespace std;

struct Value {
    int m_val {0};

public:
    auto operator <=> (const Value& rhs) const noexcept = default;
};

int main() {
    Value v1, v2;
    v1.m_val = 5;
    v2.m_val = 10;
    cout << std::boolalpha;
    cout << "v1 == v2: " << (v1 == v2) << endl;
    cout << "v1 != v2: " << (v1 != v2) << endl;
    cout << "v1 <= v2: " << (v1 <= v2) << endl;
    cout << "v1 >= v2: " << (v1 >= v2) << endl;
}
