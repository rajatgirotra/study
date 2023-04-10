/*
You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle).
You can move up, down, left, or right from and to an empty cell in one step.
Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles.
If it is not possible to find such walk return -1.

Input: grid =
[
 [0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]
],

k = 1

Output: 6
Explanation:
The shortest path without eliminating any obstacle is 10.
The shortest path with one obstacle elimination at position (3,2) is 6.
Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2)

Solution: We basically need to run a BFS (ie. put Cells in queue. deque and visit them and mark them as visited)
However as we visit each cell, we also store some state at that cell, and that is the number of obstacles you can still remove.
If you are at a cell and the obstacle count is 0, it means you can't visit any neighbor that is one.

If finally we are able to reach (m-1, n-1), we just count how many levels we have traversed.
*/

#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <string>
#include <random>
#include <algorithm>
#include <queue>
#include <tuple>
#include <set>
#include <array>
using namespace std;

struct Cell {
    int m_x{};
    int m_y{};
    int m_obsCount{};
    Cell(int x, int y, int count) : m_x(x), m_y(y), m_obsCount(count) {}

    friend bool operator < (const Cell& lhs, const Cell& rhs) noexcept {
        return std::tie(lhs.m_x, lhs.m_y) < std::tie(rhs.m_x, rhs.m_y);
    }
};

int shortest_path_with_obstacles(const vector<vector<int>>& grid, int k) {
    auto ROWS = grid.size(), COLS = grid[0].size();
    std::set<Cell> visited{};
    std::queue<Cell> q;
    q.emplace(0, 0, k);
    visited.emplace(0, 0, k);
    int count{};
    while(!q.empty()) {
        auto sz = q.size();
        for(auto i = 0; i < sz; ++i) {
            Cell c = q.front();
            q.pop();

            // have we reached the bottom?
            if(c.m_x == ROWS-1 && c.m_y == COLS-1) {
                return count;
            }

            // visit all neighbors
            static std::array<Cell, 4> dir {{{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}}};
            for(auto&& [x, y, _] : dir) {
                auto dx = c.m_x + x;
                auto dy = c.m_y + y;
                if(dx >= 0 && dx < ROWS && dy >= 0 && dy < COLS) {
                    if(visited.find(Cell(dx, dy, 0)) == visited.end()) {
                        if (grid[dx][dy] == 0) {
                            q.emplace(dx, dy, c.m_obsCount);
                            visited.emplace(dx, dy, c.m_obsCount);
                        } else if(c.m_obsCount > 0) {
                            q.emplace(dx, dy, c.m_obsCount - 1);
                            visited.emplace(dx, dy, c.m_obsCount - 1);
                        }
                    }
                }
            }
        }
        ++count;
    }
    return -1;
}

int main() {
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution dist(1, 9);

    const std::uint32_t ROWS = dist(engine), COLS = dist(engine);

    std::vector<std::vector<int>> grid;
    for(int i = 0; i < ROWS; ++i) {
        std::uniform_int_distribution dist2(0, 1);
        std::vector<int> col(COLS);
        auto gen = [&]() {
            return dist2(engine);
        };
        std::generate(begin(col), end(col), gen);
        grid.emplace_back(std::move(col));
    }

    // print grid
    cout << "Grid\n";
    for(auto&& row : grid) {
        for(auto&& val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    auto res = shortest_path_with_obstacles(grid, 2);
    cout << "Shortest path with obstacles: " << res << endl;
}
