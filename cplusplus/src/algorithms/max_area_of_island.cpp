/*
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
You may assume all four edges of the grid are surrounded by water.
The area of an island is the number of cells with a value 1 in the island.
Return the maximum area of an island in grid. If there is no island, return 0.
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
    static void dfs(vector<vector<int>>& grid, int i, int j, std::unordered_set<std::pair<int, int>>& visited,
        const vector<std::pair<int, int>>& directions, int &currentArea) {
        for (auto [r, c] : directions) {
            auto nr = i+r, nc = j+c;
            if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size() || grid[nr][nc] == 0 || visited.find({nr, nc}) != visited.end()) {
                continue;
            }
            visited.emplace(nr, nc);
            ++currentArea;
            dfs(grid, nr, nc, visited, directions, currentArea);
        }
    }

    static int maxAreaOfIsland(vector<vector<int> > &grid) {
        if (grid.empty()) return 0;

        // set of visited nodes
        vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        std::unordered_set<std::pair<int, int>> visited{};

        // We use DFS. for every visited node, we mark it as visited and then visit its neighbors.
        int rows = grid.size();
        int cols = grid[0].size();
        int maxArea = 0;
        int currentArea = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1 && visited.find({i, j}) == visited.end()) {
                    // visit all neighbors and mark them as visited.
                    visited.emplace(i, j);
                    // cout << "Found a new island at: " << i << ", " << j << endl;
                    currentArea = 1;
                    dfs(grid, i, j, visited, directions, currentArea);
                    maxArea = std::max(maxArea, currentArea);
                }
            }
        }
        return maxArea;
    }
};

class SolutionBFS {
public:
    static void bfs(vector<vector<int>>& grid, int i, int j, std::unordered_set<std::pair<int, int>>& visited,
        const vector<std::pair<int, int>>& directions, int& currentArea) {
        std::queue<std::pair<int, int>> q{};
        // visited.emplace(i, j);
        q.emplace(i, j);
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (auto [dr, dc] : directions) {
                auto nr = r + dr;
                auto nc = c + dc;
                if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size() || grid[nr][nc] == 0 || visited.find({nr, nc}) != visited.end()) {
                    continue;
                }
                visited.emplace(nr, nc);
                ++currentArea;
                q.emplace(nr, nc);
            }
        }
    }

    static int maxAreaOfIsland(vector<vector<int> > &grid) {
        if (grid.empty()) return 0;

        // set of visited nodes
        vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        std::unordered_set<std::pair<int, int>> visited{};

        // We use BFS. for every visited node, we mark it as visited and then visit its neighbors.
        int rows = grid.size();
        int cols = grid[0].size();
        int maxArea = 0;
        int currentArea = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1 && visited.find({i, j}) == visited.end()) {
                    // visit all neighbors and mark them as visited.
                    currentArea = 1;
                    visited.emplace(i, j);
                    bfs(grid, i, j, visited, directions, currentArea);
                    maxArea = std::max(maxArea, currentArea);
                }
            }
        }
        return maxArea;
    }
};


int main() {
    SolutionDFS solDFS;
    [[maybe_unused]] SolutionBFS solBFS;
    vector<vector<int>> grid1 = {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };

    vector<vector<int>> grid2 = {
        {0,0,0,0,0,0,0,0}
    };

    cout << "grid1 islands: " << solDFS.maxAreaOfIsland(grid1) << ", " << solBFS.maxAreaOfIsland(grid1) << endl;
    cout << "grid2 islands: " << solDFS.maxAreaOfIsland(grid2) << ", " << solBFS.maxAreaOfIsland(grid2) << endl;
}