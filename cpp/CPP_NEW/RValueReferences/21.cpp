#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

/* We can use std::enable_if to enable the forwarding constructor only when argument is a std::string.
 * So we need to disable it in the following cases.
 * 1) When argument is a Person, const Person, const Person&, const volatile Person etc. etc.
 * 2) When argument is a subclass of Person
 * 3) When argumen is an integral type.
 * Lets see how.
 */

struct Person {
    std::string mName;

    // template constructor
    template <typename T, typename = std::enable_if_t<
            !std::is_base_of_v<Person, std::decay_t<T>> &&
            !std::is_integral<std::remove_reference_t<T>>::value>>
    explicit Person(T&& arg) noexcept : mName(std::forward<T>(arg)) {
    }

    explicit Person(int index) : mName("ABCD") {
        cout << "Initializing Person with index c'tor\n";
    }

    // copy c'tor and other members generated automatically by the compiler
};

struct SuperPerson : public Person {
};

int main() {
    std::string name("Rajat");
    Person p(name);
    cout << p.mName << endl;

    Person p1(10);

    auto cloneP(p);

}
/* Clean solution. Infact this technique is used in std::vector. There are two constructors which accept two arguments
 * std::vector(size_type, T val);
 * std::vector(InputIterator first, InputIterator last)
 */