/*
 * C++17/20 introduces a function "int std::uncaught_exceptions()" which returns the number of exceptions that have been thrown
 * or re-thrown in the current thread and have not yet entered their catch clauses.
 *
 * If you think in your head, this function returns a value > 0 if stack unwinding is in progress. This way an object's destructor
 * can easily check if it is getting destroyed normally or as part of stack unwinding. See example below.
 */

#include <iostream>
#include <exception>
using namespace std;

struct Foo {
    bool m_normal_destruction {true};
    Foo() = default;

    ~Foo() {
        if (std::uncaught_exceptions()) {
            cout << "Foo getting destroyed as part of stack unwinding..\n";
        } else {
            cout << "Foo getting destroyed normally\n";
        }
    }
};

int main() {
    {
        Foo f;
    }

    try {
        Foo f;
        throw 5;
    } catch(...) {}
}
