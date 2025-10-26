// before cpp23, mutable lambda must specify an empty set of function parameters.

#include <print>
#include <utility>
#include <ranges>
#include <tuple>
using namespace std;

namespace rng = std::ranges;
namespace vws = std::views;

int main() {
    auto l = [i = 0, j = 1] mutable { // this is now allowed with cpp23.
        i = std::exchange(j, i+j);
        return i;
    };

    for (auto _  : vws::iota(0, 10)) {
        std::print("{} ", l());
    }
    return 0;
}