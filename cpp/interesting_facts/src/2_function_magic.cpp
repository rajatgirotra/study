#include <iostream>
#include <memory>
#include <iomanip>

using namespace std;

void someFunc() {
    cout << "someFunc called\n";
}

int main() {
    cout << "std::addressof(someFunc): " << std::addressof(someFunc) <<endl;
    cout << "someFunc: " << reinterpret_cast<void*>(someFunc) << endl;
    cout << "&someFunc: " << reinterpret_cast<void*>(&someFunc) << endl;
    cout << "someFunc == &someFunc is " << std::boolalpha << (someFunc == &someFunc) << endl;

    someFunc();

}