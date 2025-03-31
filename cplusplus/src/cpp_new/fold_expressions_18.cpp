
/*
 * folding over comma
 */
#include <type_traits>
#include <iostream>
#include <functional>
#include <string>
using namespace std;

template <typename... Args>
void FoldPrint(Args&&... args) {
    auto separateLinePrint = [](auto&& arg) {
        cout << arg << endl;
    };
    (... , separateLinePrint(std::forward<Args>(args)));
}

int main() {
    FoldPrint(10, 20., "string", string("Hello"));
}
