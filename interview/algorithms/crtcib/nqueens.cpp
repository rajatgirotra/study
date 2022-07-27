/*
 * Given a chess board of size n * n, you have to find all possible ways of putting n queens on the board so that they take down each other.
 * A queen can move horizontally, vertically or horizontally
 *
 * We can solve this using backtracking. How? We will start with row 0 and find the col where we can safely place the queen, then we will move to row 1, then row 2 and so on. Since we are visiting every row one by one, we need to remember the column where we put the queen, so that we can know the cols for the next rows where a queen can't be put. But how to store diagnol information. Note we have 2 diagnols, one with positive slope and one with negative slope.
 * for the diagnol with -ive slope, not that (r-c) i.e. (row - col) always remains constant like (0,0), (1, 1), etc. Similarly for +ive slope, (r+c) i.e. remains constant. So all we need to do is have an std::set of col, (r-c) and (r+c) values.
 *
 * We need to return a list of all possible combinations. Example,
 * Input: n = 4
 * Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
 */

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
    private:
        int n;
        std::vector<std::vector<char>> board{};
        std::vector<std::vector<string>> res{};
        std::unordered_set<size_t> cols{};
        std::unordered_set<size_t> posDiag{};  // (r+c)
        std::unordered_set<size_t> negDiag{};  // (r-c)

    public:
        explicit Solution(int arg) : n(arg) {
            // setup a board of n * n
            for(int i = 0; i < n; ++i) {
                board.emplace_back(std::vector<char>{});
                for(int j = 0; j < n; ++j) {
                    board[i].emplace_back('.');
                }
            }
        }

        auto solution() {
            backtrack(0);
            return res;
        }

        void backtrack(int r) {
            if(r == n) {
                // we found a solution. add it to res
                res.emplace_back(std::vector<string>{});
                for(auto&& row : board) {
                   res[res.size()-1].emplace_back(row.data(), n); 
                }
                return;
            }
            // iterate each col to check if we can place a queen there.
            for(int col = 0; col < n; ++col) {
                if(cols.find(col) != cols.end() ||
                   posDiag.find(r + col) != posDiag.end() ||
                   negDiag.find(r - col) != negDiag.end()) {
                    // cannot put a queen
                    continue;
                }

                // we can put a queen here. mark it on the board
                cols.emplace(col); posDiag.emplace(r + col); negDiag.emplace(r - col);
                board[r][col] = 'Q';

                // go to next row
                backtrack(r + 1);

                // we are done. lets remove the queens
                cols.erase(col); posDiag.erase(r + col); negDiag.erase(r - col);
                board[r][col] = '.';
            }
        }
};

int main() {
    Solution sol(4);
    auto result_set = sol.solution();
    for(auto&& res : result_set) {
        cout << "Solution\n----------\n";
        for(auto&& row : res) {
            cout << row << endl;
        }
        cout << "----------\n\n";
    }

    return 0;
}
