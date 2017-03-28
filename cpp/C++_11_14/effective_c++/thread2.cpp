#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;
using namespace std::literals;

void f() {
    cout << "In f\n";
    std::this_thread::sleep_for(1s);
}

int main(int argc, char *argv[])
{
    //auto fut = std::async(std::launch::async, f);
    auto fut = std::async(f);
    while (fut.wait_for(100ms) != std::future_status::ready) {
        // because we wait here, function f() never gets a chance to execute on the same thread.
        cout << "Waiting for future to be available\n";
        //std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}
