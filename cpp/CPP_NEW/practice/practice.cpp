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
using namespace std;
using namespace std::chrono;
using namespace std::literals;


auto sum() {
    return 0;
}

template <typename First, typename... Rest>
auto sum(First f, Rest... r) {
    std::common_type_t<First, Rest...> res {};
    res += sum(r...);
    return res + f;
}

int main() {
    auto x = sum(1, 2., 3.5);
    cout << x << endl;
}