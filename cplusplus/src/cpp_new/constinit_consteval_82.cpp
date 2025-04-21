/*
 * std::is_constant_evaluated() is a C++20 feature that tells you, at runtime, whether the current code is being evaluated in a
 * constant evaluation context (e.g., during constexpr evaluation). It returns true when the code is part of a constexpr evaluation, and false otherwise.
*/
#include <iostream>
#include <string>
#include <cstdint>
#include <utility>
#include <array>
#include <iterator>
#include <list>
#include <ranges>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <type_traits>

using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

constexpr bool isConstEval() {
    return std::is_constant_evaluated();
}

bool g1 = isConstEval(); // true
/*
 * Even though g1 is a bool (not constexpr), the compiler is allowed to evaluate isConstEval() at compile time if:
 *   The function is marked constexpr
 *   All arguments are constant (none here)
 *   There are no runtime-only side effects
 * This is called constant folding, and it's a compiler optimization.
 * So, even though g1 is not constexpr, the compiler might choose to evaluate isConstEval() during compilation, see that it's a constexpr function,
 * and execute it in a constant-evaluation contex
 *
 * The same call if taken inside a local scope, will be evaluated at run time.
 */

const bool g2 = isConstEval(); // true
[[maybe_unused]] static bool g3 = isConstEval(); // true
[[maybe_unused]] static int g4 = g1 + isConstEval(); // true + false (why? g1 is a runtime variable, so although g1 may be constant folded and computed at compile time, the "+ isConstEval()" will only be done by the compiler at runtime.
[[maybe_unused]] static int g5 = 42 + isConstEval(); // 42 + true (why? because 42 is a literal, so isConstEval() can be performed at compile time).

int main() {
    cout << g1 << endl;
}
