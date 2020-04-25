#pragma once

/*
 * Lets define a simple Point class with co-ordinates (x, y). Define a midpoint and mirror function to return Point objects
 * representing midpoint and mirror, and create getters and setters. First we will create simple functions then add constexpr
 */

#include <cstdint>
#include <ostream>

class Point {
    int32_t m_x {0};
    int32_t m_y {0};
public:
    constexpr Point(int32_t a = 0, int32_t b = 0) : m_x(a), m_y(b) {};

    constexpr int32_t getX() const noexcept;
    constexpr int32_t getY() const noexcept;

    constexpr void setX(int32_t val) noexcept ;
    constexpr void setY(int32_t val) noexcept ;

    constexpr Point midpoint(const Point& lhs) const noexcept ;
    constexpr Point mirror() const noexcept ;

    friend std::ostream& operator << (std::ostream& os, const Point& p) {
        os << "Point (" << p.m_x << ", " << p.m_y << ")\n";
        return os;
    }
};
