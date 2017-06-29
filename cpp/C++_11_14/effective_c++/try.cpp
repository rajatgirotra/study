#include <iostream>
using namespace std;

class A {
    public:
       template <typename T>
       void process(T* ptr) {
           cout << "Main template" << endl;
       }
};

template <>
void A::process<void>(void* ptr);

int main() {
    A a;
    void* ptr = 0;
    //char* ptr = 0;
    a.process(ptr);
    return 0;
}
