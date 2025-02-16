/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all
surrounded by water.
 */

#include <iostream>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;
namespace std {
    template<>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const noexcept {
            return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
        }
    };
}

class SolutionDFS {
public:
    static void dfs(vector<vector<char>>& grid, int i, int j, std::unordered_set<std::pair<int, int>>& visited, const vector<std::pair<int, int>>& directions) {
        for (auto [r, c] : directions) {
            auto nr = i+r, nc = j+c;
            if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size() || grid[nr][nc] == '0' || visited.find({nr, nc}) != visited.end()) {
                continue;
            }
            visited.emplace(nr, nc);
            dfs(grid, nr, nc, visited, directions);
        }
    }

    static int numIslands(vector<vector<char> > &grid) {
        if (grid.empty()) return 0;

        // set of visited nodes
        vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        std::unordered_set<std::pair<int, int>> visited{};

        // We use DFS. for every visited node, we mark it as visited and then visit its neighbors.
        int count = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && visited.find({i, j}) == visited.end()) {
                    // visit all neighbors and mark them as visited.
                    visited.emplace(i, j);
                    ++count;
                    dfs(grid, i, j, visited, directions);
                }
            }
        }
        return count;
    }
};

class SolutionBFS {
public:
    static void bfs(vector<vector<char>>& grid, int i, int j, std::unordered_set<std::pair<int, int>>& visited, const vector<std::pair<int, int>>& directions) {
        std::queue<std::pair<int, int>> q{};
        // visited.emplace(i, j);
        q.emplace(i, j);
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (auto [dr, dc] : directions) {
                auto nr = r + dr;
                auto nc = c + dc;
                if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size() || grid[nr][nc] == '0' || visited.find({nr, nc}) != visited.end()) {
                    continue;
                }
                visited.emplace(nr, nc);
                q.emplace(nr, nc);
            }
        }
    }

    static int numIslands(vector<vector<char> > &grid) {
        if (grid.empty()) return 0;

        // set of visited nodes
        vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        std::unordered_set<std::pair<int, int>> visited{};

        // We use BFS. for every visited node, we mark it as visited and then visit its neighbors.
        int count = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && visited.find({i, j}) == visited.end()) {
                    // visit all neighbors and mark them as visited.
                    visited.emplace(i, j);
                    ++count;
                    bfs(grid, i, j, visited, directions);
                }
            }
        }
        return count;
    }
};


int main() {
    SolutionDFS solDFS;
    SolutionBFS solBFS;
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    cout << "grid1 islands: " << solDFS.numIslands(grid1) << ", " << solBFS.numIslands(grid1) << endl;
    cout << "grid2 islands: " << solDFS.numIslands(grid2) << ", " << solBFS.numIslands(grid2) << endl;
}