// cpp23 adds literal suffixes for std::size_t (which is unsigned) and signed std::size_t
// suffix "t" is for signed std::size_t, and "uz" for unsigned std::size_t

#include <iostream>
#include <cstdint>
#include <print>

template <typename T>
void foo(T&&) {
    std::print("{}\n", __PRETTY_FUNCTION__);
}

int main() {
    [[maybe_unused]] auto a = 1; foo(a);
    [[maybe_unused]] auto b = 1u; foo(b);
    [[maybe_unused]] auto c = 1l; foo(c);
    [[maybe_unused]] auto d = 1ll; foo(d);
    [[maybe_unused]] auto e = 1ull; foo(e);
    [[maybe_unused]] auto f = 1.f; foo(f);
    [[maybe_unused]] auto g = 1.; foo(g);
    [[maybe_unused]] auto h = 1.l; foo(h);
    [[maybe_unused]] auto i = 1uz; foo(i);     // unsigned std::size_t
    //[[maybe_unused]]  auto j = 1t; foo(j); // signed size_t;
}