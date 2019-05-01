/*
 * Write an algorithm such that if an element in an MxN matrix is 0, its entire row and
column is set to 0.
 */

#include <iostream>
#include <set>
#include <vector>
using namespace std;

namespace {
    void matrix_zero(int A[][3], int rows, int cols) {
        std::set<int> row_indexes, col_indexes;
        for(auto i = 0; i < rows; ++i) {
            for (auto j = 0; j < cols; ++j) {
                if(A[i][j] == 0) {
                    row_indexes.insert(i);
                    col_indexes.insert(j);
                }
            }
        }

        for(auto i = 0; i < rows; ++i) {
            for (auto j = 0; j < cols; ++j) {
                if(row_indexes.find(i) != row_indexes.end()) {
                    A[i][j] = 0;
                } else if(col_indexes.find(j) != col_indexes.end()) {
                    A[i][j] = 0;
                }
            }
        }
    }
}

int main() {
    int A[4][3] = {
            {1,2,3},
            {4,0,0},
            {7,8,9},
            {1,1,1}
    };

    matrix_zero(A, 4, 3);
    for(auto i = 0; i < 4; ++i) {
        for (auto j = 0; j < 3; ++j) {
            cout << A[i][j] << "    ";
        }
        cout << endl;
    }
}