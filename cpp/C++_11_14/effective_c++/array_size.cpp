#include <iostream>
using namespace std;

template <typename T, size_t N>
constexpr size_t arraySize(T (&)[N]) noexcept {
    return N;
}

size_t arraySize(int*) {
    throw std::runtime_error("pointer types do not have sizes");
    return 0;
}

int main() {
    int keys[] {1,2,3,4,5};
    int* poKeys = keys;
    cout << arraySize(keys) << endl;
    cout << arraySize(poKeys) << endl;
    return 0;
}
    
