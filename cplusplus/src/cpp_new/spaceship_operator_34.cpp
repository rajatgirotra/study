#include <compare>
#include <iostream>
#include <iomanip>
using namespace std;

struct Base {
    int m_base_i {0};
    bool operator == (const Base& rhs) const {
        return this->m_base_i == rhs.m_base_i;
    }
    bool operator < (const Base& rhs) const {
        return this->m_base_i < rhs.m_base_i;
    }

//    auto operator <=> (const Base& rhs) const = default;
};

struct Derived : public Base {
    int m_derived_i {0};
    // auto operator <=> (const Derived& rhs) const = default;
    std::strong_ordering operator <=> (const Derived& rhs) const {
        if (this->m_base_i == rhs.m_base_i) {
            if (this->m_derived_i == rhs.m_derived_i) {
                return std::strong_ordering::equal;
            } else if (this->m_derived_i < rhs.m_derived_i) {
                return std::strong_ordering::less;
            } else {
                return std::strong_ordering::greater;
            }
        } else if (this->m_base_i < rhs.m_base_i) {
            return std::strong_ordering::less;
        }
        return std::strong_ordering::greater;
    }
};

int main() {
    Derived d1, d2;
    d1.m_base_i = 10; d1.m_derived_i = 10;
    d2.m_base_i = 10; d2.m_derived_i = 8;

    // ERROR won't compile. Why?
    // the base class also needs to define the spaceship operator otherwise compiler can't deduce the ordering with respect to base class.
    // you can change the auto return type to std::strong_ordering to make it to compile.
    cout << (d1 < d2) << endl;

    // equality works as == operator is defined which returns a bool.
    cout << (d1 == d2) << endl;
}

/* An issue with C++20 spaceship operator.
 * Given you have a class which wraps an integer and provides a ctor which takes an int. the ctor is not marked explicit, so
 * MyType x = 42; // works.
 *
 * If this function provides an operator something like this
 *
 * bool operator == (int i, const MyType& t) {
 *  return (t==i); // endless recursion.
 * }
 *
 * This results in endless recursion. Why? The compiler will have two alternatives
 * the compiler will find t.operator(MyType{i}) as i can be implicitly converted to int.
 * the compiler will try to re-write t==i as i==t, ie will find the same operator == (int, MyType) function.
 * The second one is preferred, as it does not involve an implicit type conversion, and this will cause recursion.
 *
 * However, gcc 11 catches it as an error which is good.
 * error: in C++20 this comparison calls the current function recursively with reversed arguments [-Werror]
 */
