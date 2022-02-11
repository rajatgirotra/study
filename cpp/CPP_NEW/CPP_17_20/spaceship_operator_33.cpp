/*
 * in the previous program we used
 * auto operator <=> (const MyType& rhs) const = default.
 * But what does the spaceship operator really return. it returns an object of any of the following types:
 * std::strong_ordering
 * std::weak_ordering
 * std::partial_ordering
 *
 * These ordering classes define the following static objects which are actually returned as a result of  <=> operator
 * std::strong_ordering::greater
 * std::strong_ordering::less
 * std::strong_ordering::equal/std::strong_ordering::equivalent
 * std::weak_ordering::greater
 * std::weak_ordering::less
 * std::weak_ordering::equivalent
 * std::partial_ordering::greater
 * std::partial_ordering::less
 * std::partial_ordering::equivalent
 * std::partial_ordering::unordered
 *
 * strong_ordering --> for x and y objects of a given type,
 *                     x < y (std::strong_ordering::less),
 *                     or x == y (std::strong_ordering::equal/equivalent)
 *                     or x > y (std::strong_ordering::greater)
 * And you can order/sort the elements in a defined order (ascending/descending)
 *
 * weak_ordering   --> for x and y objects of a given type,
 *                     x < y (std::weak_ordering::less),
 *                     or x == y (std::weak_ordering::equivalent)
 *                     or x > y (std::weak_ordering::greater)
 * But you can't define an order in which equivalent elements can be ordered. Example for case-insensitive strings, "hello" and "HELLO"
 * can be ordered with "hello" first or "HELLO" first.
 *
 * partial_ordering --> for x and y objects of a given type,
 *                     x < y (std::partial_ordering::less),
 *                     or x == y (std::partial_ordering::equivalent)
 *                     or x > y (std::partial_ordering::greater)
 *                     or x operand y (std::partial_ordering::unordered), because x and y could be something like NaN (not a number for floating points for example)
 * So it might not be possible to sort the elements in an ascending/descending order.
 */

#include <iostream>
#include <iomanip>
#include <compare>
#include <vector>
#include <algorithm>
using namespace std;

struct IntegerWrapper {
    int m_val {0};

public:
    std::strong_ordering operator <=> (const IntegerWrapper& rhs) const noexcept {
        return m_val == rhs.m_val ? std::strong_ordering::equal :
               m_val < rhs.m_val ? std::strong_ordering::less :
               std::strong_ordering::greater;
    }

    /* but much better and easier to define it like this
    auto operator <=> (const IntegerWrapper& rhs) const noexcept {
        return m_val <=> rhs.m_val;
    }
    */

};

struct Coord {
    double m_x {};
    double m_y {};
    double m_z {};

    auto operator <=> (const Coord& rhs) const = default;
};

int main() {
    IntegerWrapper v1, v2;
    v1.m_val = 5;
    v2.m_val = 10;
    cout << std::boolalpha;
    cout << "v1 <= v2: " << (v1 <= v2) << endl;
    cout << "v1 >= v2: " << (v1 >= v2) << endl;

    int x = 17, y = 42;
//    cout << (x <=> y) << endl; // ERROR!! no ostream for std::strong/weak/partial_ordering classes
    cout << "x <=> y == std::strong_ordering::less: " << (x <=> y == std::strong_ordering::less) << endl;

//    cout << "x <=> 17.0: " << (x <=> 17.) << endl;  // will yield std::partial_ordering::equivalent
    cout << "x <=> 17.0 == std::partial_ordering::equivalent: " << (x <=> 17. == std::partial_ordering::equivalent) << endl;  // will yield std::partial_ordering::equivalent

    std::vector<Coord> coord{{0, 5, 5}, {5, 0, 0},
                             {3, 5, 5}, {3, 0, 0},
                             {3, 5, 7}};
    std::sort(begin(coord), end(coord));

    for(auto&& c : coord) {
        cout << c.m_x << "/" << c.m_y << "/" << c.m_z << endl;
    }
}
