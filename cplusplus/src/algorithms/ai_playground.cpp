#include <iostream>
using namespace std;

class Person {
public:
    Person() {
        cout << "Person constructor\n";
    }
    ~Person() {
        cout << "Person destructor\n";
    }
};

int main() {
    auto p = new Person();
    delete p;
    return 0;
}