Very trivial!

#include <benchmark/benchmark.h>

// write a function which is under test
// function must take a State object by reference
static void someFunction(benchmark::State& s) {
   // Do any setup code here.

   for(auto _ : state) {
      // Your benchmark code will go here. this is called the measurement loop.
   }
}

// Use a MACRO to register your benchmark function and to call the main function also.
BENCHMARK(someFunction);

BENCHMARK_MAIN(); // or dont use this macro and link to benchmark_main.a