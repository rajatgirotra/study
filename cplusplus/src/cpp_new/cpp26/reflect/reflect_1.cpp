#include <meta>
#include <type_traits>
#include <vector>
using namespace std;

class X
{
    int m_data;
private:
    void foo_in_X() {}
};

void some_func(int, vector<bool>);

namespace dummy {}

enum struct Color {RED, GREEN, BLUE};

int main()
{
    constexpr auto meta_handle_1 = ^^int; // type
    constexpr auto meta_handle_2 = ^^X;
    // constexpr auto meta_handle_3 = ^^some_func;
    // constexpr auto meta_handle_4 = ^^dummy;
    constexpr auto meta_handle_5 = ^^Color;

    using T1 = [: meta_handle_1 :]; // means using T = [: meta_handle_1 :]
    using T2 = [: meta_handle_2 :]; // means using T = [: meta_handle_2 :]
    // using T3 = [: meta_handle_3 :]; // means using T = [: meta_handle_3 :]
    // using T4 = [: meta_handle_4 :]; // means using T = [: meta_handle_4 :]
    using T5 = [: meta_handle_5 :]; // means using T = [: meta_handle_5 :]

    static_assert(std::meta::is_type(meta_handle_1)); // i.e does this meta handle reflect a type.
    static_assert(std::meta::is_type(meta_handle_2));
    // static_assert(std::meta::is_type(meta_handle_3));
    // static_assert(std::meta::is_type(meta_handle_4));
    static_assert(std::meta::is_type(meta_handle_5));
}