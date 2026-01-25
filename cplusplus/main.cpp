//
// Created by rajatgirotra on 21/4/24.
//
#include <iostream>
using namespace std;

template <typename F>
void foo(F) {
    cout << __PRETTY_FUNCTION__ << " called\n";
}

enum struct Color { RED, GREEN, BLUE };

template <enum Color>
struct EnumTemplate {
    EnumTemplate() {
        [[maybe_unused]] Color c = Color::RED;
        foo(this);
    }
};

template <Color color>
struct EnumTemplate2 {
    EnumTemplate2() {
        [[maybe_unused]] Color c = Color::RED;
        foo(this);
    }
};

template <auto color>
struct EnumTemplate3 {
    EnumTemplate3() {
        [[maybe_unused]] Color c = Color::RED;
        foo(this);
    }
};

int main() {
    cout << "Hello, World!" << endl;

    [[maybe_unused]] EnumTemplate<Color::RED> et;
    [[maybe_unused]] EnumTemplate2<Color::RED> et2;
    [[maybe_unused]] EnumTemplate3<Color::RED> et3;
    return 0;
}