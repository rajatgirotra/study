/*
 * threads are moveable types and can be placed in containers.
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <iterator>
#include <mutex>
using namespace std;
using namespace std::literals;

std::mutex m_mtx;

void nothing_thread(int i) {
    {
        std::lock_guard<std::mutex> _(m_mtx);
        cout << "Doing nothing: " << i << endl;
    }
    std::this_thread::sleep_for(1s);
}

int main() {
    std::vector<std::thread> vt;
    using vt_size_type_t = std::vector<std::thread>::size_type ;
    for(vt_size_type_t i = 0; i < 5; ++i) {
        // The vector emplace_back function will call the std::thread(F&& f, Args&&... args) constructor, where F is a reference_wrapper
        vt.emplace_back(std::cref(nothing_thread), i);
        // The vector emplace_back function will call the std::thread() move constructor
//        vt.emplace_back(std::thread(nothing_thread, i));
    }

    for(auto&& t : vt) {
        t.join();
    }

//    for(vt_size_type_t i = 0; i < 5; ++i) {
//        auto t = std::move(vt[i]);
//        t.join();
//    }

    return 0;
}