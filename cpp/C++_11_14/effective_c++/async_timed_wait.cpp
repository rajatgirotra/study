#include <iostream>
#include <chrono>
#include <future>
#include <thread>
using namespace std;

void f() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "f finished on thread id: " << std::this_thread::get_id() << endl;
}

int main() {
    auto handle = std::async(std::launch::deferred, f);

    while (handle.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready);

    cout << "ending main on thread id: " << std::this_thread::get_id() << endl;
}
