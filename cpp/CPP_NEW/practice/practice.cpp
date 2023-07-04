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
using namespace std;
using namespace std::chrono;
using namespace std::literals;

// variable template
template <typename... Args>
[[maybe_unused]] auto clousre = [] (Args&&... args) {
    cout << "perfecting forwarding using variable template" << endl;
    void(std::forward<Args>(args)...);
};

[[maybe_unused]] auto clousre_2 = [](auto&&... args) {
    cout << "perfecting forwarding using variadic lambda" << endl;
    void(std::forward<decltype(args)>(args)...);

};

int main() {

}