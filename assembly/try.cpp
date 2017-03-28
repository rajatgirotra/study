#include <iostream>
#include <cstdint>
using namespace std;

int main() {
     uint64_t msr;
     
     asm volatile ( "rdtsc\n\t"    // Returns the time in EDX:EAX.
             "shl $32, %%rdx\n\t"  // Shift the upper bits left.
             "or %%rdx, %0"        // 'Or' in the lower bits.
             : "=a" (msr)
             :
             : "rdx");
     
     cout << "msr: " << msr << endl;

          asm volatile ( "rdtsc\n\t"    // Returns the time in EDX:EAX.
             "shl $32, %%rdx\n\t"  // Shift the upper bits left.
             "or %%rdx, %0"        // 'Or' in the lower bits.
             : "=a" (msr)
             :
             : "rdx");

     cout << "msr: " << msr << endl;

     return 0;
}
