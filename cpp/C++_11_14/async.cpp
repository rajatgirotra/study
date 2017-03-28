#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std;

void foo() {
    cout << "Foo executing" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main() {
    std::async(std::launch::async, foo);
    return 0;
}
