#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

// 3rd - using enable_if to provide specialization

template <typename T, typename Enable = void>
class A {
 public:
  A() {
    cout << "Primary template\n";
  }
};

// partial specialization for floating point
template <typename T>
class A<T, std::enable_if_t<std::is_floating_point_v<T>>> {
//class A<T, std::enable_if_t<std::is_floating_point_v<T>, int>>
 public:
  A() {
    cout << "Partial specialization template for floating point\n";
  }

};

int main(int argc, char* argv[]) {
  A<int> a1; // int is not floating point, so partial specialization doesnt even exist for it.
  A<double> a2; // two template class will be found one A<double, void> and the other also A<double, void>, but
  // the second one is choosen as it is more specialized.
  return 0;
}