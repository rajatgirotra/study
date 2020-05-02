/*
 * you have two very simple lambda's.
 * 1) Doesnt capture anything, no params and returns an int
 * 2) Doesnt capture anything, one int param and returns param*10
 *
 * Create a Callable that if called without args, calls first lambda and if called with int arg, calls second lambda
 *
 * Hint: As lambda are closure objects, just inherit from the closure classes.
 */

#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

template <typename L1, typename L2>
struct SomeFunctionObject : public L1, L2
{
    SomeFunctionObject(L1 l1, L2 l2) : L1(std::move(l1)), L2(std::move(l2)) {};
    using L1::operator();
    using L2::operator();
};

template <typename L1, typename L2>
auto make_combined(L1&& l1, L2&& l2) {
    //return SomeFunctionObject<L1, L2>();
    return SomeFunctionObject<std::decay_t<L1>, std::decay_t<L2>>(std::forward<L1>(l1), std::forward<L2>(l2));
}

int main() {
    auto l1 = []() {return 5; };

    auto l2 = [](int arg) {
        return arg * 10;
    };

    cout << l1() << "\n" << l2(10) << endl;

    // this doesnt work as the default SFO ctor will call the ClosureType default ctor and ClosureType default ctor are implicitly
    // deleted.
    //SomeFunctionObject<decltype(l1), decltype(l2)> sfo; // try with SFO ctor commented out

    // this doesnt work as l1 and l2 are lvalue references, so in SFO L1 and L2 are deduced to be a reference.
    // and you cannot derive from a reference. ie struct SFO: public L1, L2 is a problem.
    //auto sfo = make_combined(l1, l2); // try with SFO ctor commented out

    // try with SFO ctor commented out
    // same problem, ClosureType default ctor is implicitly deleted.
    //auto sfo = make_combined(std::move(l1), std::move(l2));

    //auto sfo = make_combined(l1, l2);
    SomeFunctionObject<decltype(l1), decltype(l2)> sfo(l1, l2);

    cout << "some function object: " << sfo() << "\n";
    cout << "some function object: " << sfo(10) << "\n";
    return 0;
}