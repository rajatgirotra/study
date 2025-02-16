/*
You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
Connect: A cell is connected to adjacent cells horizontally or vertically.
Region: To form a region connect every 'O' cell.
Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.

Basically, you need to change all 'O' to 'X' where 'O' form a region (i.e. 'O's should be together horizontally and vertically).
Just that if any '0' in a region is on the boundary, then we can surround it with 'X's.

Solution is very simple. We visit the boundary of the matrix. If there is any '0' we perform a dfs to visit all '0's and mark them safe (i.e change them to '#')
Then we traverse the whole grid and convert all '0's to 'X' and also mark the safe nodes back to '0'.
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
    struct hash<std::pair<int, int> > {
        size_t operator()(const std::pair<int, int> &p) const noexcept {
            return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
        }
    };
}

class Solution {
public:

    static void dfs(vector<vector<char>> & board, int i, int j, const unordered_set<std::pair<int, int>>& visited) {
        // mark board[i, j] as safe
        board[i][j] = '#';
        static std::vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for (auto [dr, dc] : directions) {
            auto nr = i + dr;
            auto nc = j + dc;
            if (nr < 0 || nr >= board.size() || nc < 0 || nc >= board[0].size() || board[nr][nc] != 'O' || visited.find({nr, nc}) != visited.end()) {
                continue;
            }
            board[nr][nc] = '#';
            dfs(board, nr, nc, visited);
        }
    }

    void solve(vector<vector<char> > &board) {
        if (board.empty()) return;
        int rows = board.size();
        int cols = board[0].size();
        std::unordered_set<std::pair<int, int>> visited{};
        for (int i = 0; i  < rows; ++i) {
            if (board[i][0] == 'O') dfs(board, i, 0, visited);
            if (board[i][cols-1] == 'O') dfs(board, i, cols-1, visited);
        }
        for (int j = 0; j  < cols; ++j) {
            if (board[0][j] == 'O') dfs(board, 0, j, visited);
            if (board[rows-1][j] == 'O') dfs(board, rows-1, j, visited);
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }
};

int main() {
    Solution sol;

    vector<vector<char> > board1 = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };

    sol.solve(board1);
    cout << "Board: " << endl;
    for (auto &row: board1) {
        for (auto &cell: row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}
