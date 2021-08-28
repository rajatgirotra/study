/*
 * template <typename M, typename T>
 * void my_mem_fun(M T::* pm);
 *
 * What does M and T mean? Remember this pattern. This means T is some class and T::* is a pointer to non-static member function
 * or member data of that class T. and M is the function type or the data type.
 */

#include <iostream>
using namespace std;

template <typename M, typename T>
void my_mem_fn(M T::* pm);

struct Foo {
    void display_greeting() const noexcept { cout << "Seasons greetings!!"; }

    double data {89.89};
};

int main() {
    /*
     * undefined reference to `void my_mem_fn<void () noexcept const, Foo>(void (Foo::*)() noexcept const)'
     * i.e. M = void () noexcept const and T = Foo
     */
    my_mem_fn(&Foo::display_greeting);

    /*
     * undefined reference to `void my_mem_fn<double, Foo>(double Foo::*)'
     * i.e. M = double, T = Foo
     */
    my_mem_fn(&Foo::data);

}


