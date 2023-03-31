/* Given two integer array's x and y of same size representing the Points (x, y) in a 2 plane
   Return a list of squares that can be formed using those points.
*/

#include <iostream>
#include <ostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
using namespace std;

struct Point {
    int m_x {};
    int m_y {};

    Point(int x, int y) : m_x(x), m_y(y) {}

    friend bool operator < (const Point& lhs, const Point& rhs) noexcept {
        return std::tie(lhs.m_x, lhs.m_y) < std::tie(rhs.m_x, rhs.m_y);
    }

    friend ostream& operator << (ostream& os, const Point& rhs) {
        os << "(" << rhs.m_x << ", " << rhs.m_y << ")";
        return os;
    }
};

struct Square {
    Point m_p1;
    Point m_p2;
    Point m_p3;
    Point m_p4;

    Square(const Point& a, const Point& b, const Point& c, const Point& d) : m_p1(a), m_p2(b), m_p3(c), m_p4(d) {
        std::vector<Point> tmp {m_p1, m_p2, m_p3, m_p4};
        std::sort(begin(tmp), end(tmp));
        m_p1 = tmp[0];
        m_p2 = tmp[1];
        m_p3 = tmp[2];
        m_p4 = tmp[3];
    }

    friend bool operator < (const Square& lhs, const Square& rhs) noexcept {
        return std::tie(lhs.m_p1, lhs.m_p2, lhs.m_p3, lhs.m_p4) < std::tie(rhs.m_p1, rhs.m_p2, rhs.m_p3, rhs.m_p4);
    }

    friend ostream& operator << (ostream& os, const Square& rhs) {
        os << "[ " << rhs.m_p1 << ", " << rhs.m_p2 << ", " << rhs.m_p3 << ", " << rhs.m_p4 << " ]";
        return os;
    }
};

std::uint64_t euclidean(const Point& a, const Point& b) {
    //return static_cast<std::uint64_t>(sqrt(pow(a.m_x - b.m_x, 2) + pow(a.m_y - b.m_y, 2)) * 1000);
    return static_cast<uint64_t>(pow(a.m_x - b.m_x, 2) + pow(a.m_y - b.m_y, 2));
}

bool is_square(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    auto d12 = euclidean(p1, p2);
    auto d13 = euclidean(p1, p3);
    auto d14 = euclidean(p1, p4);
    auto d23 = euclidean(p2, p3);
    auto d24 = euclidean(p2, p4);
    auto d34 = euclidean(p3, p4);
    std::array<std::uint64_t, 6> lengths{d12, d13, d14, d23, d24, d34};

    std::unordered_map<std::uint64_t, std::uint64_t> m{};
    for(auto&& len : lengths) {
        auto& count = m[len];
        ++count;
    }

    // validate
    if(m.size() != 2) { return false; }//  only two entries expected. One for side and one for diagnol
    auto iter = m.begin();
    auto& x = *iter;
    ++iter;
    auto& y = *iter;
    if(!((x.second == 4 && y.second == 2) || (x.second == 2 && y.second == 4))) return false; // count should be 4 and 2.

    auto side = x.first, diagnol = y.first;
    if(x.second == 2) {
        side = y.first;
        diagnol = x.first;
    }

    if(2*side != diagnol) return false;
    return true;

}

template <std::size_t N>
auto get_squares(const std::array<int, N>& x, const std::array<int, N>& y) {
    // key is the distance between two points.
    // value is a set of pairs of points with the same distance.
    using DMap = std::unordered_map<std::uint64_t, std::set<std::pair<Point, Point>>>;
    DMap dMap;

    for(size_t i = 0; i < N - 1; ++i) {
        Point a(x[i], y[i]);
        for(size_t j = i+1; j < N; ++j) {
            Point b(x[j], y[j]);
            auto d = euclidean(a, b);
            auto& dSet = dMap[d];
            dSet.emplace(a, b);
        }
    }

    std::set<Square> result;
    for(size_t i = 0; i < N - 1; ++i) {
        Point a(x[i], y[i]);
        for(size_t j = i+1; j < N; ++j) {
            Point b(x[j], y[j]);
            auto&& dSet = dMap[euclidean(a, b)];
            for(auto&& [p1, p2] : dSet) {
                if(is_square(a, b, p1, p2)) {
                    //cout << "Result is true\n";
                    result.emplace(a, b, p1, p2);
                }
            }
        }
    }

    return result;
}

int main() {
    std::array<int, 7> x{-1, -1, -1, 0, 0, 0, 1};
    std::array<int, 7> y{-1, 0, 1, -1, 0, 1, 0};

//    std::array<int, 4> x{-1, -1, 0, 0};
    //   std::array<int, 4> y{-1, 0, 0, 1};

    auto result = get_squares(x, y);
    for(auto&& sq : result) {
        cout << sq << endl;
    }
}
