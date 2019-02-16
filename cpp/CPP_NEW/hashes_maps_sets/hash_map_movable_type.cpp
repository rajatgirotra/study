#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
using namespace std;

struct Foo {
    static int count;
    int tag;
    Foo();
    ~Foo();
};

int Foo::count = 0;
Foo::Foo() : tag(++count) {}

Foo::~Foo() {
    cout << "destroying foo with tag: " << tag << endl;
}

int main() {
    std::unordered_map<string, unique_ptr<Foo>> hashMap;

    auto& foo1 = hashMap["Hello"];
    foo1.reset(new Foo());

    hashMap["Hello"] = std::make_unique<Foo>();

    {
        auto f2 = std::make_unique<Foo>();
        hashMap["Hello"] = std::move(f2);
    }

    auto result = hashMap.emplace("Hello", std::make_unique<Foo>());
    if(!result.second) {
        cout << "Failed to insert\n";
    }

}

/*
 Watch from Sean Parent Runtime Polymorphism.
 */