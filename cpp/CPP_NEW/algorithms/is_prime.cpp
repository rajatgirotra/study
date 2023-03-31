#include <iostream>
#include <cmath>
#include <charconv>
using namespace std;

bool isPrime(std::uint64_t n) {
    if(n <= 1) return false;
    else if (n == 2 || n == 3) return true;
    std::uint32_t start = 2;
    while(start*start <= n) {
        if(n % start == 0) {
            return false;
        }
        ++start;
    }
    return true;
}

int main() {
    for(int i = 0; i < 30; ++i) {
        cout << "isPrime(" << i << "): " << isPrime(static_cast<uint64_t>(i)) << endl;
    }
}