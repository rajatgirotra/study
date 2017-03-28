//Catching SIGSEGV (segmentation fault using sigaction)
#include <csignal>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void onSegmentationFault(int signalNo, siginfo_t* info, void*)
{
    cout << "Signal Number: " << signalNo << endl;
    switch(signalNo)
    {
        case SIGSEGV:
            cout << "Segmentation Fault occurred.\nSigNo: " << info->si_signo << "\nErrno: " << info->si_errno
                 << "\nCode: " << info->si_code << "\nPID: " << info->si_pid << endl;
            exit(1);
            break;
        default:
            cout << "Unhandled signal: " << signalNo << endl;
            break;
    }
}

int main()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &onSegmentationFault;
    act.sa_flags = SA_SIGINFO;
    //Install your signal handler
    sigaction(SIGSEGV, &act, 0);



    cout << "I will be output: " << getpid() << endl;
    int* a = 0;
    *a = 9;
    
    cout << "I will not be output" << endl;
    return 0;
}
