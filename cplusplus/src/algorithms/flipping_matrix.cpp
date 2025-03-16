/*
. Flipping the Matrix

Sean invented a game involving a 2𝑛 × 2𝑛 matrix where each cell of the matrix contains an integer. He can reverse any of its rows or columns any
number of times. The goal of the game is to maximize the sum of the elements in the n×n submatrix located in the upper-left quadrant of the matrix.
Given the initial configurations for matrix, help Sean reverse the rows and columns of each matrix in the best possible way so that the sum of the
elements in the matrix's upper-left quadrant is maximal.
 */

#include <array>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
using namespace std;

constexpr int N = 6;

auto flipping_matrix(std::array<std::array<int, N>, N>& matrix) {
  int maxSum = 0;
  for(int i = 0; i < N/2; i++) {
    for(int j = 0; j < N/2; j++) {
      std::array<int, 4> tmp{ matrix[i][j], matrix[i][N-1-j], matrix[N-1-i][j], matrix[N-1-i][N-1-j] };
      maxSum = *std::max_element(begin(tmp), end(tmp));
    }
  }
  return maxSum;
}

int main() {
  static_assert(N%2 == 0, "N must be even");
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist (-20, 20);

  auto gen = [&] () { return dist(engine); };

  std::array<std::array<int, N>, N> matrix{};
  for(int i = 0; i < N; ++i) {
    std::generate(begin(matrix[i]), end(matrix[i]), gen);
  }

  cout << "Input matrix: "<<  endl;
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      cout << std::setw(4) <<  matrix[i][j] << " ";
    }
    cout << endl;
  }

  auto maxSum = flipping_matrix(matrix);
  cout << "Max sum: " << maxSum << endl;
}