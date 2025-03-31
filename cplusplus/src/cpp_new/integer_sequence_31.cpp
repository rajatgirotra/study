#include <iostream>
#include <utility>
#include <array>
#include <tuple>
#include <fstream>
using namespace std;

template <typename T, T... Ints>
void print_sequence(const std::integer_sequence<T, Ints...>&) {
    cout << "print_sequence of " << sizeof...(Ints) << ":";
    ((cout << " " << Ints), ...);
    cout << endl;
}

template <typename Tuple, size_t... Ints>
ostream& printElements(ostream& os, const Tuple& t, const std::index_sequence<Ints...>&) {
    ((os << std::get<Ints>(t) << (Ints < std::tuple_size_v<Tuple> - 1 ? ", " : "")),...);
    return os;
}
template <typename... Types>
ostream& operator << (ostream& os, const std::tuple<Types...>& tpl) {
    os << "(";
    printElements(os, tpl, std::index_sequence_for<Types...>{});
    os << ")";
    return os;
}

template <typename Arr, size_t... Ints>
auto a2t_impl(const Arr& arr, const std::index_sequence<Ints...>&) {
    return std::make_tuple(arr[Ints]...);
}

template <typename T, size_t N>
auto a2t(const std::array<T, N>& arr) {
    return a2t_impl(arr, std::make_index_sequence<N>{});
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
