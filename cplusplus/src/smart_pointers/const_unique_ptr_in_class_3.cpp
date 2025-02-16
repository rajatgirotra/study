/*
 * try to create a const std::unique_ptr array in a class holding pointers to classes A, B, C.
 */

#include <iostream>
#include <memory>
#include <array>
#include <vector>
using namespace std;

struct Base {
    virtual ~Base() = default;
};

struct A : Base {};
struct B : Base {};
struct C : Base {};

namespace {
    template<typename T, typename... Args>
    auto initArray(Args&&... args) {
        std::vector<std::unique_ptr<T>> vec;
        vec.reserve(sizeof...(args));
        (vec.emplace_back(std::forward<Args>(args)), ...);
        return vec;
    }
}

class Holder {
private:
//     trivial attempt. Fails with error: error: ISO C++ forbids flexible array member ‘m_array’
//    const std::unique_ptr<Base> m_array[] {
//            std::make_unique<A>(),
//            std::make_unique<B>(),
//            std::make_unique<C>()
//    };

//     need to hard code number 3; which isn't the best choice.
//    const std::unique_ptr<Base> m_array[3] {
//        std::make_unique<A>(),
//        std::make_unique<B>(),
//        std::make_unique<C>()
//    };

    // wrap in std::array. that again needs size.
//    const std::array<std::unique_ptr<Base>, 3> m_array {
//        std::make_unique<A>(),
//        std::make_unique<B>(),
//        std::make_unique<C>()
//    };

    // use vector. But fails. Why? because std::initializer_list<> elements must be copyable
    // std::unique_ptr<> is only moveable type
//    const std::vector<std::unique_ptr<Base>> m_array {
//        std::make_unique<A>(),
//        std::make_unique<B>(),
//        std::make_unique<C>()
//    };

    // Correct solution, use a helper

public:
    const std::vector<std::unique_ptr<Base>> m_array = initArray<Base>(
                    std::make_unique<A>(),
                    std::make_unique<B>(),
                    std::make_unique<C>()
            );
};

int main() {

}
