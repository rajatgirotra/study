/*
 * You have an array of +ive integers. Each integer represents the height of one side of a container.
 * You have to find the maximum volume of water that can be stored in the container.
 *
 * The approach is very simple. Use left and right pointers. Calculate the volume and update the max volume.
 * The difference between the left and right pointers is the width of the container.
 */

#include <unordered_map>
#include <vector>
#include <ranges>
#include <iostream>
#include <random>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

template <size_t N>
size_t max_volume_of_water(const std::array<int, N>& arr) {
    size_t l{}, r{N-1};
    size_t max_volume{};
    while(l < r) {
        size_t vol = (r-l) * std::min(arr[l], arr[r]);
        max_volume = std::max(max_volume, vol);
        arr[l] < arr[r] ? ++l : --r;
    }
    return max_volume;
}

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dest(1, 15);
    std::array<int, 6> arr{};
    auto gen = [dest = std::move(dest), engine = std::move(engine)] () mutable  {
        return dest(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    auto res = max_volume_of_water(arr);
    cout << "Array: " ;
    rng::copy(arr, std::ostream_iterator<int> (cout, ", "));
    cout << "\nMax volume of water that can be stored in the container is: " << res << "\n";
}