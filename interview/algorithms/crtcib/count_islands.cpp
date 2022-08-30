/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Basically, when you find an island, you need to look at all neighbors (left, right, up and down) and if those are also one, then dont increase the count of islands and mark them as visited.
So you will need to maintain an std::pair<int, int> of cells you have visited before.
*/


#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_set>
#include <array>
#include <set>
using namespace std;

namespace std {
    template<typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        size_t operator() (const std::pair<T1, T2>& p) const noexcept {
            return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
        }
    };
}

class Solution {
   public:
       //void bfs(int r, int c, std::vector<std::vector<char>>& grid, set<pair<int, int>>& visited) {
       void bfs(int r, int c, std::vector<std::vector<char>>& grid, unordered_set<pair<int, int>>& visited) {
           // A queue is normally used for BFS
           queue<std::pair<int, int>> q;

           // mark this island as visited.
           visited.emplace(r, c);

           static std::array<std::pair<int, int>, 4> directions {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};

           // add this cell to q and then start iterating the queue just like in normal BFS
           q.emplace(r, c);

           while(!q.empty()) {
               auto [tr, tc] = q.front();
               q.pop();
               for(auto [dr, dc] : directions) {
                   auto qr = tr+dr, qc = tc + dc;
                   if((qr >= 0) && (qr < grid.size()) && (qc >= 0) && (qc < grid[0].size()) &&
                      (grid[qr][qc] == '1') &&
                      (visited.find(std::make_pair(qr, qc)) == visited.end())) {
                      q.emplace(qr, qc);
                      visited.emplace(qr, qc);
                   }
               }
           }
       }

       int numIslands(std::vector<std::vector<char>>& grid) {
           if(grid.empty()) return 0; // base case
           // grid[n] is a row.
           // first lets get the count of rows and cols
           int rows = grid.size(), cols = grid[0].size();

           //set<pair<int, int>> visited{}; 
           unordered_set<pair<int, int>> visited{}; 
           int island_count = 0;
 
           // iterate each cell in row major order
           for(int r = 0; r < rows; ++r) {
               for(int c = 0; c < cols; ++c) {
                   if (grid[r][c] == '1' && (visited.find(std::make_pair(r, c)) == visited.end())) {
                       bfs(r, c, grid, visited); // only start a BFS if this cell is 1 and never visited before.
                       island_count += 1;  // only increment this if you are visiting this for the first time.
                   }
               }
           }

           return island_count;
       }
};

int main() {
}
