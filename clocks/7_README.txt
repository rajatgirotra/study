Let me write some more about the TSC instruction that i have learnt.
Ok the simplest way to benchmark a piece of code is to read the TSC counter of the CPU
before and after the code you are trying to benchmark. You can easily write code in assembly that reads
TSC using the "rdtsc" instruction. Note that TSC counter maintains the number of CPU clock cycles expended.

Problem 1
==========

READ_TSC_BEFORE_USING_RDTSC
    BENCHMARK_CODE
READ_TSC_AFTER_USING_RDTSC

The problem is that intel cpu's can execute code out of order. That means you can never be sure that the BENCHMARK_CODE will always execute
after reading the 1st TSC and before reading the 2nd TSC.

The way out is to use a CPU serializing instruction; which guarantees that all code before the instruction will have completed. And no code
after the instruction will have started. It turns out we have an assembly instruction "CPUID" which provides the needed serialisation. 

Problem 2
=========

It turns out that the number of clock cycles expended by the CPUID instruction introduces a lot of variance and therefore we loose out on the
measurement resolution. It does work; so we can still use it in case we do not want to be THAT ACCURATE.


SOLUTION
========

Modern CPU's now provide an instruction called "rdtscp" will reads the CPUID and the TSC together. So it has this pseudo property of serializing by making
sure that all instruction BEFORE it are executed. Therefore we have a new solution

“The RDTSCP instruction waits until all previous instructions have been executed
before reading the counter. However, subsequent instructions may begin execution
before the read operation is performed.”

CPUID #serialize
READ_TSC_BEFORE_USING_RDTSC # read tsc using rdtsc not rdtscp
    BENCHMARK_CODE
READ_TSC_AFTER_USING_RDTSCP
    OTHER_CODE


NEW PROBLEM
==========

A new problem now arises. RDTSCP cannot guarantee that code written after it will not execute before it. This means that any code from the "OTHER_CODE"
section can execute before RDTSCP contaminating your benchmark. So the final solution is to place a call to CPUID after RDTSCP. This will guarantee
the needed serialization.

FINAL SOLUTION
==============

CPUID #serialize
READ_TSC_BEFORE_USING_RDTSC # read tsc using rdtsc not rdtscp
    BENCHMARK_CODE
READ_TSC_AFTER_USING_RDTSCP
CPUID
    OTHER_CODE

Next lets try to do some benchmarking.
