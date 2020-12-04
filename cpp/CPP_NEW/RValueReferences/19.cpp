#include <iostream>
#include <string>
#include <set>
#include <array>
#include <chrono>
#include <type_traits>
using namespace std;
using namespace std::literals;

std::set<std::string> namesSet;

std::array<std::string, 5> namesArr {"Rajat", "Vidhu", "Myra", "Viraj", "Shweta"};

template <typename T>
void addName(T&& arg);

// called for non-integral types
template <typename T>
void addNameImpl(T&& arg, std::false_type) {
    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    cout << "addName(T&& args) called at: " << now << ", adding: " << arg << " to set\n";
    namesSet.insert(std::forward<T>(arg));
}

template <typename T>
void addNameImpl(T&& arg, std::true_type) {
    addName(namesArr.at(static_cast<unsigned long>(arg)));
}

// function taking universal reference to add names to the namesSet
template <typename T>
void addName(T&& arg) {
    addNameImpl(std::forward<T>(arg), typename std::is_integral<std::remove_reference_t<T>>::type());
}

/* It is an exercise why we need std::remove_reference<> above. Think what could be template argument be if "arg" is an lvalue"
 */


int main() {
    short s = 1;
    addName(s);
    for(auto&& name : namesSet) {
        cout << "Name: " << name << endl;
    }
}

/* Use tag dispatching and add a second parameter to the addName() function for integral and non-integral types.
 * Tag dispatch is very trivial. Just define different types and each type will specify to distinguish an overload.
 *
 * In the above case also, we could have used simple types like struct A{}; struct B{}; also.
 * Before discussing the std::enable_if solution lets see a related problem next
 */