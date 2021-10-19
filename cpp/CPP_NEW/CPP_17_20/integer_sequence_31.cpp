/*
 * template <typename T, T... Ints>
 * std::integer_sequence;
 * The class template std::integer_sequence represents a compile-time sequence of integers. When used as an argument to a
 * function template, the parameter pack Ints can be deduced and used in pack expansion. defined in <utility> header
 *
 * template<std::size_t... Ints>
 * using index_sequence = std::integer_sequence<std::size_t, Ints...>; // alias template for T = std::size_t
 *
 * template<class T, T N>
 * using make_integer_sequence = std::integer_sequence<T, a sequence 0, 1, 2, ..., N-1 >;
 *
 * template<std::size_t N>
 * using make_index_sequence = std::make_integer_sequence<std::size_t, N>;
 *
 * template<class... T>
 * using index_sequence_for = std::make_index_sequence<sizeof...(T)>;
 */

#include <iostream>
#include <utility>
#include <array>
#include <tuple>
using namespace std;
namespace {
    template <typename T, T... Ints>
    void print_sequence(const std::integer_sequence<T, Ints...> seq) {
        cout << "print_sequence of " << seq.size() << ":";
        ((cout << " " << Ints), ...);
        cout << endl;
    }
}

template <typename T, std::size_t... I>
auto a2t_impl(const T& arr, const std::index_sequence<I...>) {
    return std::make_tuple(arr[I]...);
}

template <typename T, std::size_t N>
auto a2t(const std::array<T, N>& arr) {
    return a2t_impl(arr, std::make_index_sequence<N>{});
}


// function to output a tuple
template <typename T, std::size_t... I>
void print_tuple(ostream& os, const T& arg, std::index_sequence<I...>) {
    ((os << (I == 0 ? "" : ", ") << std::get<I>(arg)), ...);
}

template <typename... Args>
ostream& operator << (ostream& os, const std::tuple<Args...>& t) {
    os << "(";
    print_tuple(os, t, std::make_index_sequence<sizeof...(Args)>{});
    return os << ")";
}

int main() {
    print_sequence(std::integer_sequence<unsigned, 3, 0, 98, 23, 67, 7, 12>{});
    print_sequence(std::index_sequence<4, 8, 0, 98, 12345, 789>{});
    print_sequence(std::make_integer_sequence<unsigned, 10>{});
    print_sequence(std::make_index_sequence<10>{});
    print_sequence(std::index_sequence_for<float, double, string, char>{});

    // function which uses std::index_sequence to convert std::array to tuple
    std::array<int, 4> arr {1, 2, 3, 4};

    auto tuple = a2t(arr);
    static_assert(std::is_same_v<decltype(tuple), std::tuple<int, int, int, int>>);

    cout << tuple << endl;
}
