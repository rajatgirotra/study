/*
Matrix chain multiplcation. given a sequence of matrices A1, A2, .., An; compute the optimum way of
parenthesis that minimizes the number of scalar multiplications.

Two matrices A(i, j) and B(j, k) can be multiplied if and only if number of cols of first == number of rows of second.
and the resultant matrix size if number of rows of first * number of cols of second. ie (i, k) in this case.

We say that every matrix A(i) in the input has dimensions p(i-1) * p(i), where p(i) is actually the number of cols of each matrix.
except p(0) which is the number of rows of the first matrix

*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <array>
using namespace std;

template <size_t N>
void print_matrix_chain_order(size_t s[][N], size_t i, size_t j) {
    if(i == j) {
        cout << "A" << i << " ";
    } else {
        cout << "( ";
        print_matrix_chain_order(s, i, s[i][j]);
        print_matrix_chain_order(s, s[i][j]+1, j);
        cout << ") ";
    }
}


template <size_t SZ>
void matrix_chain_multiplication(const std::array<size_t, SZ>& arr) {
    constexpr size_t N = SZ-1;
    size_t m[N+1][N+1] {};
    size_t s[N+1][N+1] {};

    for(size_t i = 1; i <= N; ++i) {
        m[i][i] = 0;
    }

    auto distance = 1;
    while(distance < N) {
        for(size_t i = 1; i <= N - distance; ++i) {
            auto j = i + distance;
            m[i][j] = std::numeric_limits<size_t>::max();
            for(size_t k = i; k <= j-1; ++k) {
                auto tmp = m[i][k] + m[k+1][j] + (arr[i-1]*arr[k]*arr[j]);
                if(tmp < m[i][j]) {
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
            cout << "m[" << i << "][" << j << "]: " << m[i][j] << endl;
        }
        ++distance;
    }

    cout << "Min matrix multiplication: " << m[1][N] << endl;
    print_matrix_chain_order(s, 1, N);
    cout << endl;
}

size_t m[7][7] {};

// SZ will be N+1, where N is the number of matrices.
template <size_t SZ>
size_t matrix_chain_lookup(const std::array<size_t, SZ>& arr, size_t i, size_t j) {
    if(i == j) {
        return 0;
    } else if(m[i][j] != std::numeric_limits<size_t>::max()) {
        return m[i][j];
    } else {
        for(size_t k = i; k <= j-1; ++k) {
            auto tmp = matrix_chain_lookup(arr, i, k) + 
                       matrix_chain_lookup(arr, k+1, j) + 
                       (arr[i-1]*arr[k]*arr[j]);
            if(tmp < m[i][j]) {
                m[i][j] = tmp;
            }
        }
    }
    return m[i][j];
}


template <size_t SZ>
size_t memoized_matrix_chain(const std::array<size_t, SZ>& arr) {
    constexpr size_t N = SZ-1;
    
    for(size_t i = 1; i <= N; ++i) {
        for(size_t j = 1; j <= N; ++j) {
            m[i][j] = std::numeric_limits<size_t>::max();
        }
    }
    return matrix_chain_lookup(arr, 1, N);
}

int main() {
    std::array<size_t, 7> arr {30, 35, 15, 5, 10, 20, 25};
    // std::array<size_t, 7> arr {5, 10, 3, 12, 5, 50, 6};
    cout << "Array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    cout << endl;
    matrix_chain_multiplication(arr);
    cout << endl;

    cout << "Recursive Memoized matrix chain: " << memoized_matrix_chain(arr) << endl;
}
