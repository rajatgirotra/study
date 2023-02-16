#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <mutex>
#include <syncstream>
#include <latch>
#include <chrono>
#include <cxxabi.h>
#include <typeinfo>
#include <semaphore>
#include <random>
#include <thread>
using namespace std;

#define USE_CPU_FENCE 0
#define USE_SINGLE_HW_THREAD 1

#if USE_SINGLE_HW_THREAD == 1
#include <sched.h>
#include <cassert>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <pthread.h>
#endif

std::string demangled_name(const char* mangled_name) {
    int res{-1};
    auto name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
    string demangled(name);
    if(res != 0) {
        return mangled_name;
    } else {
        free(name);
        return demangled;
    }
}

auto syncOut = [](std::ostream& os = std::cout) {
    return std::osyncstream(os);
};

int X = 0, Y = 0, r1 = 0, r2 = 0;
std::counting_semaphore<2> endSema(0);
std::binary_semaphore beginSema1(0), beginSema2(0);

void threadOne() {
    while(true) {
        // wait on semaphore
        beginSema1.acquire();

        // introduce random delay
        static std::random_device r;
        static std::default_random_engine engine(r());
        std::uniform_int_distribution<uint32_t> dist(1, 10000);
        while(dist(engine) % 8 != 0);

        // set X and get r2
        X = 1;
#if USE_CPU_FENCE == 1
        asm volatile("mfence" ::: "memory");
#elif USE_SINGLE_HW_THREAD == 1
        asm volatile("" ::: "memory");
#endif
        r2 = Y;
        // signal endSema
        endSema.release();
    }
}

void threadTwo() {
    while(true) {
        // wait on semaphore
        beginSema2.acquire();

        // introduce random delay
        static std::random_device r;
        static std::default_random_engine engine(r());
        std::uniform_int_distribution<uint32_t> dist(1, 10000);
        while(dist(engine) % 8 != 0);

        // set Y and get r1
        Y = 1;
#if USE_CPU_FENCE == 1
        asm volatile("mfence" ::: "memory");
#elif USE_SINGLE_HW_THREAD == 1
        asm volatile("" ::: "memory");
#endif
        r1 = X;

        // signal endSema
        endSema.release();
    }
}


int main() {
    std::jthread t1(std::cref(threadOne));
    std::jthread t2(std::cref(threadTwo));

#if USE_SINGLE_HW_THREAD == 1
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(6, &cpus);
    if(pthread_setaffinity_np(t1.native_handle(), sizeof(cpu_set_t), &cpus) != 0) {
        syncOut() << "sched_setaffinity failed with error: " << strerror(errno) << endl;
        return 1;
    }
    if(pthread_setaffinity_np(t2.native_handle(), sizeof(cpu_set_t), &cpus) != 0) {
        syncOut() << "sched_setaffinity failed with error: " << strerror(errno) << endl;
    }

#endif

    int reorders = 0;
    int iterations = 0;
    do {
        X = Y = r1 = r2 = 0;
        beginSema1.release();
        beginSema2.release();

        endSema.acquire();
        endSema.acquire();

        if(r1 == 0 && r2 == 0) {
            syncOut() << ++reorders << " reorders in " << iterations << " iterations\n";
        }
    } while(++iterations <= std::numeric_limits<int>::max() - 10);
}