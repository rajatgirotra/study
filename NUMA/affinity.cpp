/* taskset internally first calls sched_setaffinity() and then calls execve to start your program
taskset -c 0 ./a.out
So the above command will set the affinity to cpu 0. If in your program, you call sched_setaffinity(), the earlier one will get overridden. Also

1) sched_(set/get)affinity()'s first parameter is a thread id or process id. You can always get process id using getpid() and for thread id (use gettid() or a direct system call) as shown below.

2) Using the function above with a process id will only apply the affinity to the main thread. Not other threads. You can test that by running this program and setting different cpu masks to both thread from command line using taskset.

We'll soon move to how NUMA Control API can be used which provides memory affinity and cpu affinity both.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <sched.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
using namespace std;

void print_affinity() {
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    #ifdef SYS_gettid
    auto tid = syscall(SYS_gettid);
    #endif
    // cout << "Thread id: " << tid << endl;
    if(sched_getaffinity(tid, sizeof(cpu_set_t), &cpus) == 0) {
        for (int i = 0; i < 4; ++i) {
            if (CPU_ISSET(i, &cpus)) {
                cout << "Thread id " << tid << " has affinity to CPU " << i << endl;
            }
        }
    } else {
        perror("sched_getaffinity error: ");
        abort();
    }
}

int main() {
    #ifdef SYS_gettid
    cout << "Main thread id: " << syscall(SYS_gettid) << endl;
    #endif

    std::thread new_thread([] () {
        while (true) {
            print_affinity();
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    });
        
    while (true) {
        print_affinity();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    new_thread.join();
    return 0;
}
