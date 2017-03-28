/* Install handler for catching multiple signals in a multi threaded program
 * and study the behavior.
 */
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <csignal>
#include <execinfo.h>
#include <thread>
#include <chrono>
using namespace std;


void signalHandler(int signalNo, siginfo_t* info, void*)
{
    switch(signalNo)
    {
        case SIGINT: 
            cout << "Main thread interrupted (SIGINT) by process with id: " << info->si_pid << endl;
            exit(1);
            break;
        case SIGQUIT:
            cout << "Main thread interrupted (SIGQUIT) by process with id: " << info->si_pid << endl;
            exit(1);
            break;

        case SIGABRT:
            cout << "Main thread aborted (SIGABRT) by process with id: " << info->si_pid << endl;
            exit(1);
            break;

        case SIGTERM:
            cout << "Main thread terminated (SIGTERM) by process with id: " << info->si_pid << endl;
            exit(1);
            break;
        case SIGSEGV:
            cout << "Program received SIGSEGV" << endl;
            void* array[10];
            int size;
            size = backtrace(array, 10);
            backtrace_symbols_fd(array, size, STDERR_FILENO);
            exit(1);
            break;
        default:
            cout << "Unhandled signal: " << signalNo << endl;
            exit(1);
    }
}

void t1()
{

   //Sleep for 15 seconds.
    std::this_thread::sleep_for(std::chrono::seconds(15));
}

int main()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));

    act.sa_sigaction = &signalHandler;
    act.sa_flags = SA_SIGINFO;

    //sigaction(SIGINT, &act, 0);
    //sigaction(SIGQUIT, &act, 0);
    //sigaction(SIGABRT, &act, 0);
    //sigaction(SIGTERM, &act, 0);
    //sigaction(SIGSEGV, &act, 0);

    std::thread t(&t1);
    //t.join();
    return 0;
}

