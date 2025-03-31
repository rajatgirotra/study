/*
 * REMEMBER THAT subsumption works ONLY with concepts. As compiler builds a subsumption graph to find out which concept subsumes other concepts and if one concept
 * is more constrained compared to another one.
 */
#include <concepts>
#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
concept HasDraw_c = requires (T obj) {
    obj.draw();
};

template <typename T>
concept HasDrawAndCompare_c = requires (T obj) {
    obj.draw();
    obj = obj;
};

template <HasDrawAndCompare_c T>
void print(T) {
    cout << "Print for HasDrawAndCompare_c\n";
}

template <HasDraw_c T>
void print(T) {
    cout << "Print for HasDraw_c\n";
}

struct X {
public:
    void draw() {}
};

int main() {
    X x;

    //error: call of overloaded ‘print(X&)’ is ambiguous
    print(x); // should be an ambiguous call as HasDrawAndCompare_c doesn't subsume HasDraw.
}

/*
 * template<typename T>
 * concept RgSwap = std::ranges::input_range<T> && std::swappable<T>;
 *
 * template<typename T>
 * concept ContCopy = std::ranges::contiguous_range<T> && std::copyable<T>;
 *
 * Here the ContCopy is more constrained. because contiguous_range concept subsumes input_range and std::copyable subsumes swappable (you can check
 * their implementation on cppreference).
 * So we should be aware of which standard concepts subsume which ones.
 */