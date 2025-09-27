/*
 * C++20 onwards non type template parameters are allowed. What can be non type template parameters?
 * 1. integral types
 * 2. floating types
 * 3. enum types
 * 4. pointers and references
 * 5. members variable/functions pointers and references
 * 6. capture-less lambdas
 * 7. structural types class objects.. huh?? really.
 */

#include <iostream>
#include <string>

using namespace std;

template <typename T>
void bar(T&& value = T()) {
    cout << __PRETTY_FUNCTION__ << " with value: " << value << endl;
}

template <typename T>
struct member_variable : std::false_type {};

template <typename T, typename C>
struct member_variable<C T::*> : std::true_type {};

template <auto N>
void foo() {
    if constexpr (member_variable<decltype(N)>::value) {
        bar<decltype(N)>(); // T in bar will be an integer pointer.
    }
    else {
        bar(N);
    }
}

enum struct Color {
    RED,
    GREEN,
    YELLOW,
};

ostream& operator<<(ostream& os, const Color& color) {
    switch (color) {
        case Color::RED: os << "RED"; break;
        case Color::GREEN: os << "GREEN"; break;
        case Color::YELLOW: os << "YELLOW"; break;
    }
    return os;
}

struct MyClass {
    double m_real;
    int m_int;

    std::string dwim(bool) const;
};

static const int VALUE = 10;
constexpr const int* pValue = &VALUE;
const int& valueRef = VALUE;

struct StaticConfig {
    int m_i;
    double m_d;
};

static constexpr StaticConfig tiny{1, 1.};
static constexpr StaticConfig huge{1000, 1000.};

template <StaticConfig Config>
struct Application {
    void app() { cout << "in Application::foo with Config: " << Config.m_i << ", " << Config.m_d << endl; }
};

int main() {
    // integral
    foo<5>();
    foo<true>();

    // floating point
    foo<10.65>();
    foo<10.65f>();

    // enum types
    foo<Color::RED>();

    // pointers and references
    foo<&VALUE>(); // pointer
    foo<pValue>(); // pointer (will fail to compile if pValue is not constexpr)
    // n C++20, a non-type template argument must be a constant expression of a permitted type (integral, pointer, reference, structural object, etc.).
    // so &VALUE qualifies, because it is an address of a constant expression.
    // pValue does not qualify, as it is a runtime variable holding a pointer value, and variables cannot be used as NTTPs.
    // if you make pValue constexpr, then yes you can use it.

    [[maybe_unused]] MyClass myClass;
    myClass.m_real = 3.14;
    myClass.m_int = 42;
    foo<&MyClass::m_int>();

    auto l = [] (const int x) { return x*x;};
    foo<l>();

    /* this is a great way to create Config, or Policy classes or any other thing which is known at compile time. */
    Application<tiny> tinyApp;
    tinyApp.app();

    Application<huge> hugeApp;
    hugeApp.app();
}