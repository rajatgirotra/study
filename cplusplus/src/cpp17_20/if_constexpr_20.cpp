/*
 * if constexpr allows you to simplify a lot of tricks we do around SFINAE and tag dispatch. and the syntax looks more natural.
 * Let's see
 */

#include <iostream>
#include <type_traits>
#include <functional>
using namespace std;

// function overload depending on argument type is integral or not.
// Note you have to write two template overloads and is much more code.
// we can also achieve the same via tag dispatch also. (shown below)
template <typename T>
std::enable_if_t<std::is_integral_v<T>> simpleTypeInfo([[maybe_unused]] T t) {
    cout << "integral version\n";
}

template <typename T>
std::enable_if_t<!std::is_integral_v<T>> simpleTypeInfo([[maybe_unused]] T t) {
    cout << "non-integral version\n";
}

// doing same as above using tag dispatch
template<typename T>
void simpleTypeInfoTagImpl([[maybe_unused]] T t, [[maybe_unused]] std::true_type) {
    cout << "integral version\n";
}

template<typename T>
void simpleTypeInfoTagImpl([[maybe_unused]] T t, [[maybe_unused]] std::false_type) {
    cout << "non-integral version\n";
}


template <typename T>
void simpleTypeInfoTag(T t) {
    simpleTypeInfoTagImpl(t, std::is_integral<T>{});
}

// doing the same with elegant constexpr
template <typename T>
void simpleTypeInfoConstexpr([[maybe_unused]] T t) {
    if constexpr (std::is_integral_v<T>) {
        cout << "integral version\n";
    } else {
        cout << "non-integral version\n";
    }
}

int main() {
    // using SFINAE
    simpleTypeInfo(10);
    simpleTypeInfo(10.);

    // using tag dispatch
    simpleTypeInfoTag(10);
    simpleTypeInfoTag(10.);

    // using constexpr
    /*
     * the else part will be discarded by the compiler in this case. strictly speaking the compiler will only discard portions
     * of the else part which are dependent on template parameter T. all other statements should still compile and have proper syntax.
     */
    simpleTypeInfoConstexpr(10);

    simpleTypeInfoConstexpr(10.);

}
