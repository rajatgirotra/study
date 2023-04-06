/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
Example:
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]

Input: n = 1
Output: [["Q"]]

 It is a backtracking problem.
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    static void solveNQueens(int n, int row, vector<vector<string>>& res,
                             vector<vector<char>>& board,
                             std::unordered_set<int>& cols,
                             std::unordered_set<int>& posDiag,
                             std::unordered_set<int>& negDial) {
        if(row == n) {
            std::vector<string> tmp;
            for(auto&& r : board) {
                std::string str{};
                str.assign(begin(r), end(r));
                tmp.push_back(str);
            }
            res.push_back(tmp);
            return;
        }

        for(int c = 0; c < n; ++c) {
            if(cols.count(c) || negDial.count(row-c) || posDiag.count(row+c)) {
                continue;
            }
            cols.emplace(c);
            negDial.emplace(row-c);
            posDiag.emplace(row+c);
            board[row][c] = 'Q';

            solveNQueens(n, row+1, res, board, cols, posDiag, negDial);

            board[row][c] = '.';
            cols.erase(c);
            negDial.erase(row-c);
            posDiag.erase(row+c);
        }
    }

    static vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<vector<char>> board(static_cast<unsigned long>(n), std::vector<char>(static_cast<unsigned long>(n), '.'));
        for(auto&& x : board) {
            for(auto&& y : x) {
                cout << y;
            }
            cout << endl;
        }
        std::unordered_set<int> cols{};
        std::unordered_set<int> posDiag{};
        std::unordered_set<int> negDiag{};
        solveNQueens(n, 0, res, board, cols, posDiag, negDiag);
        return res;
    }
};

int main() {
    auto res = Solution::solveNQueens(8);
    cout << "Solution: [ ";
    for(auto x = 0u; x < res.size(); ++x) {
        auto&& ways = res[x];
        cout << "[";
        for(auto i = 0u; i < ways.size(); ++i) {
            cout << "\"" << ways[i] << "\"" << (i < ways.size()-1 ? ", " : "");
        }
        cout << "]" << (x < res.size()-1 ?  ", " : "");
    }
    cout << " ] \n";
}