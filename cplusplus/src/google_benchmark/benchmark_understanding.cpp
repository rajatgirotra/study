#include <benchmark/benchmark.h>
#include <iostream>
#include <thread>
using namespace std;

static void DoSetup([[maybe_unused]] const benchmark::State& state) {
    static int i = 0;
    cerr << "DoingSetup: " << ++i << endl;
}

static void DoTeardown([[maybe_unused]] const benchmark::State& state) {
    cerr << "DoingTeardown\n";
}

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}
BENCHMARK(BM_StringCopy)->Name("StringCopy")->Setup(DoSetup)->Teardown(DoTeardown)->Threads(1);


static void BM_PrintIterations(benchmark::State& state) {
    static int repetition_counter = 0;  // optional global to track setup

    // Increment repetition counter manually if needed
    for (auto _ : state) {
        // Each loop iteration inside state
        benchmark::DoNotOptimize(_);
    }

    // Print info at the end of this repetition
    std::cout << "Repetition #" << ++repetition_counter
              << ", iterations = " << state.iterations()
              << ", thread_id = " << std::this_thread::get_id()
              << "\n";
}

BENCHMARK(BM_PrintIterations)->Repetitions(1)->Threads(2); // 20 runs of your function. Default repetition is 10 and 10 for both threads.

static void BM_TestArgs(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(_);
    }
}
// BENCHMARK(BM_TestArgs)
//     ->Args({1<<10, 128})
//     ->Args({2<<10, 128})
//     ->Args({4<<10, 128})
//     ->Args({8<<10, 128})
//     ->Args({1<<10, 512})
//     ->Args({2<<10, 512})
//     ->Args({4<<10, 512})
//     ->Args({8<<10, 512});

BENCHMARK(BM_TestArgs)->Ranges({{1<<10, 8<<10}, {128, 512}});
BENCHMARK(BM_TestArgs)->ArgsProduct({ {8, 32}, {16, 64} });

BENCHMARK_MAIN();