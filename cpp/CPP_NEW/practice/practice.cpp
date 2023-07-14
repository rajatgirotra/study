#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <mutex>
#include <syncstream>
#include <latch>
#include <chrono>
#include <cxxabi.h>
#include <typeinfo>
#include <semaphore>
#include <random>
#include <thread>
#include <exception>
#include <system_error>
#include <unordered_map>
#include <string_view>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <set>
#include <type_traits>
#include <string>
#include <memory>
#include <cassert>
#include <array>
#include <variant>
#include <iomanip>
#include <typeinfo>
#include <random>
#include <iterator>
#include <ranges>
#include <cmath>
using namespace std;
using namespace std::chrono;
using namespace std::literals;

/*
 * return all prime numbers strictly less than given number n.
 */

bool is_prime(int N) {
    if(N < 2) return false;
    else if (N == 2 || N == 3) return true;
    for(int i = 2; i <= static_cast<int>(sqrt(N)); ++i) {
        if(N % i == 0) return false;
    }
    return true;
}

int count_primes(int N) {
    int res {};
    for(int i = 2; i <= N; ++i) {
        if(is_prime(i)) {
            ++res;
            cout << i << " ";
        }
    }
    cout << endl;
    return res;
}

int main() {
    int n = 70;
    cout << count_primes(n) << endl;
}