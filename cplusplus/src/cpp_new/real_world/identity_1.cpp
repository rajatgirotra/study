/*
 * Write a function template identity<T> that returns its argument unchanged. Call it with int, double, std::string.
 */

#include <print>
#include <string>

namespace
{
    // return argument should be unchanged, so we return a universal reference
    template <typename T>
    T&& identity(T&& arg)
    {
        return std::forward<T>(arg);
    }
}

int main()
{
    static_assert(std::is_same_v<int&&, decltype(identity<int>(42))>);
    static_assert(std::is_same_v<double&&, decltype(identity<double>(42))>);

    double d = 22.7;
    static_assert(std::is_same_v<double&, decltype(identity(d))>);

    static_assert(std::is_same_v<std::string&&, decltype(identity<std::string>("Hello World"))>);
}