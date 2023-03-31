/*
 * return all prime numbers strictly less than given number n.
 */

#include <iostream>
#include <array>
#include <vector>
#include <cmath>
using namespace std;

bool isPrime(std::uint32_t  n) {
    if(n <= 1) { return false; }
    else if(n == 2 || n == 3) { return true;}
    auto start = 2U;
    while(start * start <= n) {
        if(n % start == 0) {
            return false;
        }
        ++start;
    }
    return true;
}

void mark_composites(vector<bool>& primes, std::uint32_t i) {
    std::uint32_t k = 2u;
    for(auto j = i*k; j < primes.size(); ++k, j = i*k) {
        primes[j] = true;
    }
}

int count_primes(int n) {
    // primes[i] = false means i is prime
    // primes[i] = true means i is composite
    std::vector<bool> primes(static_cast<vector<bool>::size_type>(n)+1, false);
    for(auto i = 0U; i < static_cast<uint32_t>(std::ceil(std::sqrt(n))); ++i) {
        if (!primes[i]) {
            if(!isPrime(i)) {
                primes[i] = true;
            } else {
                mark_composites(primes, i);
            }
        }
    }

    int count{};
    for(auto i = 0u; i < primes.size(); ++i) {
        if(!primes[i]) {
            cout << i << " is prime\n";
            ++count;
        }
    }
    return count;
}

int main() {
    int n = 30;
    cout << count_primes(n) << endl;
}