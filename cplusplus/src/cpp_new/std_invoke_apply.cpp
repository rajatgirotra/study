#include <iostream>
#include <functional>
#include <tuple>
using namespace std;

int add(int a, int b) { return a + b; }

struct S {
    int m_a;
    int add(int b) { return m_a + b; }
};

// some sort of coarse implementation
namespace MyNS {
    template<typename F, typename... Args>
    auto invoke(F f, Args&&... args) -> decltype(auto) {
        return f(std::forward<Args>(args)...);
    }

    template<typename F, typename TupleType>
    auto apply(F f, TupleType&& tpl) -> decltype(auto) {
        return [&]<std::size_t... N>(std::index_sequence<N...>) -> decltype(auto) {
            return f(std::get<N>(std::forward<TupleType>(tpl))...);
        }(std::make_index_sequence<std::tuple_size_v<std::decay_t<decltype(tpl)>>>{});
    }

}

int main() {
    //very trivial.
    auto res = std::invoke(add, 3, 4);
    cout << res << endl;

    S s{42};
    cout << s.add(4) << endl;

    // std::apply is very similar to std::invoke but is mostly used for tuple like elements.
    // which have an std::get<> interface to fetch individual elements.
    std::tuple tpl{&s, 4};
    cout << std::apply(&S::add, tpl) << endl; // params must be packed in a tuple

    cout << MyNS::apply(add, std::tuple(3, 4)) << endl;
}

