#include <iostream>
#include <functional>
using namespace std;

int main() {
    // hello world in a non-intuitive way.
    [out = std::ref(cout << "Hello ")] () {
        out.get() << "World\n";
    }();
}

/*
 * cout << "Hello " is immediately executed and that returns an ostream&. That ostream& is captured in std::reference_wrapper<>
 * using std::ref() and then fetched inside the body of the lambda using out.get().
 *
 * Do remember that std::reference_wrapper<> can also wrap a Callable in which case the class provides a function call operator
 * but here we are not wrapping a Callable, just an ostream reference.
 */
