#include "ce14.hpp"
#include <iostream>

using namespace  std;
constexpr int32_t Point::getX() const noexcept { return m_x; }

constexpr int32_t Point::getY() const noexcept { return m_y; }

constexpr void Point::setX(int32_t val) noexcept { m_x = val; }

constexpr void Point::setY(int32_t val) noexcept { m_y = val; }

constexpr Point Point::midpoint(const Point &lhs) const noexcept {
    return Point(static_cast<int>(m_x + lhs.m_x)/2, static_cast<int>(m_y + lhs.m_y)/2);
}

constexpr Point Point::mirror() const noexcept {
    return Point(-m_x, -m_y);
}

constexpr Point reflection(const Point& rhs) noexcept {
    Point result; // create a non-const Point
    result.setX(-rhs.getX());
    result.setY(-rhs.getY());
    return result;
}
int main(int argc, char** argv) {
    constexpr Point p1(10, 20);
    constexpr Point p2(20, 30);
    cout << p1;
    cout << p2;
    constexpr auto mid = p1.midpoint(p2);
    cout << "midpoint: " << mid;
    cout << "mirror: " << p1.mirror();
    cout << p1.getX() << " " << p1.getY() << endl;

    constexpr auto reflectMid = reflection(mid); // will be computed at compile time. You can try to put an unresolved symbol to check.
    cout << "reflectMid: " << reflectMid;
}