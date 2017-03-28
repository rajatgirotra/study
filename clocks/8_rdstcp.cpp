#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
using namespace std;

int main()
{
    //Let try to create a vector, and do a push_back() 1 million times and then see how long it takes
    //Make sure you turn off optimization; otherwise the optimizer can optimize away all your code.
    //for (auto i = 0; i < 1000000; ++i)
    for (auto i = 0; i < 10000; ++i)
    {
        uint64_t cycles_low, cycles_high, cycles_low1, cycles_high1;
        __asm__ __volatile__ ( "cpuid \n\t"
                               "rdtsc \n\t"
                               "mov %%rdx, %0\n\t"
                               "mov %%rax, %1\n\t" : "=r" (cycles_high), "=rm" (cycles_low) :: "%rax","%rbx","%rcx","%rdx");

        vector<int> v;
        v.push_back(42);
        __asm__ __volatile__ ( "rdtscp \n\t"
                               "mov %%rdx, %0\n\t"
                               "mov %%rax, %1\n\t"
                               "cpuid \n\t" : "=r" (cycles_high1), "=rm" (cycles_low1) :: "%rax","%rbx","%rcx","%rdx");


        uint64_t start = ( ((uint64_t)cycles_high << 32) | cycles_low );
        uint64_t end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );

        cout << "start: " << start << ", end: " << end << ", end-start: " << end-start << " clock_cycles" << endl;
    }

    return 0;
}

// Note that rdtsc loads the TSC in EDX:EAXi (or RDX:RAX if you talk about 64 bits). Higher order 32 bits in EDX and lower order 32 bits in EAX.
