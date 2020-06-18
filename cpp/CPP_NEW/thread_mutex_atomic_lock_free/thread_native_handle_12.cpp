/*
Because every OS/kernel has its own API and thread implementation, its not possible for c++ standard to standardize everything,
so it provides a native_handle() api which returns the underlying handle of the threading API. Let's see
*/
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <vector>
#include <cxxabi.h>
#include <string>
#include <cassert>
#include <typeinfo>
using namespace std;

namespace {
    string demangle(const char* mangled_name) {
        int result {};
        auto demagled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &result);
        assert(result == 0);
        string s(demagled_name);
        free(demagled_name);
        return s;
    }
}


int main() {
    std::mutex iomutex;
    std::thread t = std::thread([&iomutex] () {
        std::lock_guard<std::mutex> lck(iomutex);
        cout << "Inside thread, thread id: " << std::this_thread::get_id() << endl;
        cout << "Inside thread, pthread_self: " << pthread_self() << endl;
    });

    {
        std::lock_guard<std::mutex> lck(iomutex);
        cout << "thread t id: " << t.get_id() << endl;
        cout << "thread t native_handle: "<< t.native_handle() << endl; // on x86
        cout << "native handle type on x86: " << demangle(typeid(decltype(declval<std::thread>().native_handle())).name()) << endl;
    }

    t.join();
    return 0;
}
