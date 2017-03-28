#include "43.h"
#include <iostream>
using std::endl;
using std::cout;

class A{};

struct B {
    B(int) {};
};

struct C {
    C() = delete;
};

struct D {
    // deleting copy c'tor also deletes default c'tor
    // but the reverse is not true as you see in C.
    // also move c'tor will be deleted as there is
    // no explicitly move c'tor defined.
    D(const D&) = delete;
};

struct E {
    // Only copy assignment and move assignment operator
    // will be deleted.
    E& operator = (const E&) = delete;
};

struct F {
    // F(const F&) = delete;
    F(F&&) = default;
};

struct G {
    G& operator = (G&&) = default;
};

int main(int argc, char *argv[]) {
    print_type_traits<A>();
    print_type_traits<B>();
    print_type_traits<C>();
    print_type_traits<D>();
    // D d;
    print_type_traits<E>();
    print_type_traits<F>();
    // F f;
    print_type_traits<G>();
    return 0;
}
