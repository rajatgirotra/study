
/*
You are given a 2d matrix which consist of the following symbols ., # and *, where . represents free cell, # represents an obstacle, and * denotes shape. Your task is to find out the minimum obstacle to remove from the matrix so that the shapes falls down to the bottom.
Test Case:
[["*", "*", "*", "*"],
["#", "*", ".", "*"],
[".", ".", "#", "."],
[".", "#", ".", "#"] ]

Output = 4
Simulation:
Initial matrix:
[["*", "*", "*", "*"],
["#", "*", ".", "*"],
[".", ".", "#", "."],
[".", "#", ".", "#"] ]

After removing matrix[1][0]
[[".", ".", ".", "."],
["*", "*", "*", "*"],
[".", "*", "#", "*"],
[".", "#", ".", "#"] ]

After removing matrix[2][2], matrix[3][1], matrix[3][3], we get
[[".", ".", ".", "."],
[".", ".", ".", "."],
["*", "*", "*", "*"],
[".", "*", ".", "*"] ]

which will give us the output 4
*/

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

int toMove(const std::vector<std::vector<char>>& grid) {
    // find how many steps the shape needs to move down such that
    // it reaches the bottom.
    int rows = grid.size();
    int steps_down{};
    for(int r = rows-1; r >= 0; --r) {
        auto&& row = grid[r];
        auto iter = std::find_if(begin(row), end(row), [](char c) {
            return c == '*';
        });
        if(iter == row.end()) ++steps_down;
        else break;
    }
    return steps_down;
}

int getObstacles(const std::vector<std::vector<char>>& grid, int rowStart, int rowEnd, int c) {
//    int rows = grid.size(), cols = grid[0].size();
    int count{};
    for(int r = rowStart; r <= rowEnd; ++r) {
        if(grid[r][c] == '#') ++count;
    }
    return count;
}

int solution(const std::vector<std::vector<char>>& grid) {
    int steps = toMove(grid);
    int rows = grid.size(), cols = grid[0].size();

    int rowStart = rows - steps - 1;
    int obstacle_count {};
    for(int r = rowStart; r >= 0; --r) {
        for(int c = 0; c < cols; ++c) {
            if (grid[r][c] == '*') {
                obstacle_count += getObstacles(grid, r+1, r+steps, c);
            }
        }
    }
    return obstacle_count;
}

int main() {
    std::vector<std::vector<char>> grid;
    grid.push_back(std::vector<char>{'*', '*', '*', '*'});
    grid.push_back(std::vector<char>{'#', '*', '.', '*'});
    grid.push_back(std::vector<char>{'.', '.', '#', '.'});
    grid.push_back(std::vector<char>{'.', '#', '.', '#'});

    auto res = solution(grid);
    cout << "solution: " << res << endl;
}