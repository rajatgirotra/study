#include <iostream>
#include <csignal>
#include <cstdio>
#include <thread>
#include <chrono>
#include <unistd.h>
using namespace std;

char* tmpFileName = "rajat.tmp";

void cleanup(int)
{
    cout << "Unlinking in signal handler\n" << endl;
    unlink(tmpFileName);
    exit(1);
}

int main()
{
    //install a signal handler
    typedef void(*sh_t)(int);
    sh_t pH = signal(SIGINT, cleanup);
    if(pH == SIG_ERR)
        cout << "Could not install Signal Handler\n" << endl;
    FILE* fp = fopen(tmpFileName, "rw");
    if(fp == 0)
        cout << "Could not open file" << endl;
    fclose(fp);
    std::this_thread::sleep_for(std::chrono::seconds(15));
    unlink(tmpFileName);

    return 0;
}

