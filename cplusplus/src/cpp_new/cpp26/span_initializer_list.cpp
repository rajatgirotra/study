/*
 * cpp26 has added a new constructor for std::span<> which takes a std::initializer_list
 */

#include <span>
#include <initializer_list>
#include <print>
#include <array>
using namespace std;

void use_data(std::span<const int> data) { // const int is important.
    std::println("data size: {}, first element: {}", data.size(), data[0]);
}

int main() {
    use_data({1, 2, 3, 4});
    // use_data(std::array {1, 2, 3, 4});
}
