
#include <type_traits>
#include <iostream>
#include <functional>
#include <string>
using namespace std;

template <typename... Args>
void FoldPrint(Args&&... args) {
    (std::cout << ... << std::forward<Args>(args)) << "\n";
}

int main() {
    FoldPrint(10, 20., "string", string("Hello"));
}

/* if you see the result, its all combined together "1020stringHello"
 * to get more control over printing/formatting we can always fold over comma operator which is very very useful.
 * folding over comma allows to call any Callable over and over - once for every template argument.
 * lets see folding over comma now.
 */