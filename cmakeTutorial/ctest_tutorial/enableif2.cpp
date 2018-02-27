#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

// 1st - using enable_if in function return types
template <typename T, typename... Args>
typename std::enable_if<std::is_floating_point_v<T>, double>::type construct(T* t, Args&&... args) {
  cout << "Constructing using double return type\n";
};

template <typename T, typename... Args>
typename std::enable_if<std::is_integral_v<T>, bool>::type construct(T* t, Args&&... args) {
  cout << "Constructing using bool return type\n";
};

int main(int argc, char* argv[]) {
  int* poT = 0;
  construct(poT, 10); // since T is int ie integral type, the first overload will not be considered.
}