/*
Given a sequence of matrices, find the most efficient way to multiply these matrices together.
The efficient way is the one that involves the least number of multiplications.

The dimensions of the matrices are given in an array arr[] of size N (such that N = number of matrices + 1)
where the ith matrix has the dimensions (arr[i-1] x arr[i]).

Basically we need to fully parenthesize the matrix chain multiplication problem such that the number of scalar multiplications is minimized.
We will solve using this recurrence relation:

m[i, j] = 0 if i == j
m[i, j] = m[i, k] + m[k+1, j] + p(i-1) * p(k) * p(j) for i <= k < j
where m[i, j] is the minimum number of scalar multiplications needed to compute the matrix A[i]A[i+1]...A[j]

We need to consider all possible k values and choose the one that minimizes the number of scalar multiplications.
We also need to print this parenthesization.
*/

#include <iostream>
#include <limits>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    void printChainOrder(const vector<int>& arr, const vector<vector<pair<int, int>>>& m, int i, int j) {
        if (i == j) {
            cout << "A" << i << " ";
        } else {
            cout << "(";
            printChainOrder(arr, m, i, m[i][j].second);
            printChainOrder(arr, m, m[i][j].second + 1, j);
            cout << ")";
        }
    }

    void matrixChainOrder(const vector<int>& arr) {
        // m[i, j] will be pair<int, int> where pair.first will the count of least scalar multiplications and
        // pair.second will be the k value that minimizes the count.
        int N = arr.size() - 1; // N is the matrix count.
        vector<vector<pair<int, int>>> m(arr.size(), vector<pair<int, int>>(arr.size(), {0, 0}));

        for (int l = 2; l <= N; ++l) {
            for (int i = 1; i<= N - l + 1; ++i) {
                auto j = i + l - 1;
                m[i][j].first = std::numeric_limits<int>::max();
                for (int k = i; k < j; ++k) {
                    auto res = m[i][k].first + m[k+1][j].first + (arr[i-1] * arr[k] * arr[j]);
                    if (res < m[i][j].first) {
                        m[i][j].first = res;
                        m[i][j].second = k;
                    }
                }
            }
        }
        cout << "Minimum number of scalar multiplications: " << m[1][N].first << endl;
        printChainOrder(arr, m, 1, N);
        cout << endl;
    }
};

int main() {
    vector<int> arr1{30, 35, 15, 5, 10, 20, 25};
    vector<int> arr2{5, 10, 3, 12, 5, 50, 6};

    Solution s;
    s.matrixChainOrder(arr1);
    s.matrixChainOrder(arr2);
}