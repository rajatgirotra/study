/*
 * cpp26 introduces saturating math operations. i.e. operations that do not let you overflow the size of the integral type
 * you are working with. these are defined in numeric.
 */
#include <numeric>
#include <cstdint>
#include <print>
#include <cxxabi.h>
#include <string>
using namespace std;

namespace {
    auto demangle(const char* mangled_name) {
        int res {-1};
        auto s = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
        string sres (mangled_name);
        if (res == 0) {
            sres = s;
            free(s);
        }
        return sres;
    }
}

template <typename T>
void print_type_and_value(T&& t) {
    std::println("type: {}, value: {}", demangle(typeid(T).name()), std::forward<T>(t));
}

int main() {
    constexpr std::uint8_t val = 140;
    auto newVal = val + val; // will automatically promote val to int
    print_type_and_value(newVal);

    // however, if I want to add and not have any overflow, I can use saturating add
    static_assert(std::add_sat(val, val) == 255); // addition will be saturated to 255.

    // similarly you have div_sat, sub_sat, mul_sat
    constexpr std::uint8_t val2 = 142;
    auto newVal2 = std::sub_sat(val, val2); // result will not go negative for uint8_t
    print_type_and_value(newVal2);

    // you also have saturate_cast<> which will cast a high value down to the maximum value for that type.
    static_assert(std::saturate_cast<std::int8_t>(255) == 127);
    static_assert(std::saturate_cast<std::uint8_t>(300) == 255);
    static_assert(std::saturate_cast<std::int16_t>(300) == 300); // 300 will remain 300 as it fits std::int16_t
    static_assert(std::saturate_cast<std::int16_t>(32768) == 32767);
    static_assert(std::saturate_cast<std::uint16_t>(65536) == 65535);
}