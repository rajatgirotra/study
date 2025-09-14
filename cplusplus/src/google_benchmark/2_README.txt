The output from a benchmark run can be on console or json or csv format. default is console but json/csv is useful if you want to programmatically parse the benchmark results and display in UI.

Every benchmark result has two things
1. context -- details/metadata about the run (You can very easily add your own user defined context in addition to the default context)
2. benchmark results.

Use --benchmark_format=<console|json|csv> or BENCHMARK_FORMAT env variable. In general, for every CLI option --option_flag, there is a corresponding OPTION_FLAG env variable available. get complete list using --help option of the binary. CLI always overrides env configuration.

--benchmark_filter=<regex> # to only run benchmarks that match this regex.

For broken benchmarks function, just put the DISABLED_ prefix and they will be disabled at runtime.

How benchmarks are run
=======================
google benchmarking library will automatically run your code under test (i.e. the BM function) several times. In each run, the number of iterations (i.e. the measurement loop) is decided dynamically in order to get a statistically stable result. Example: in 1st run, iterations may be 1, in 2nd run 100, 3rd run 1000 and so on until it gets statistically consistent results. If your "code under test" runs really fast, of course it will run for more iterations. slower code will run for fewer iterations. After benchmark has found the statistically stable iterations, you can ask it to run that iterations multiple times using the Repetitions(count) function. See "BENCHMARK(BM_PrintIterations)->Repetitions(1)->Threads(1);" in benchmark_understanding.cpp

For each test, you can set the "MinTime" you want that test to run. Google will run it for at least MinTime to maximum 5X the MinTime. You can set this time either at the time of benchmark function registration (in code) or at runtime using CLI option. Default for MinTime is 0.5 seconds.

it is also advisable to warm up your code before calculating benchmark numbers to get stable results. this is done so that any caching effects on the code in the initial runs are neutralized. google benchmark can do this for you by not accounting for some of the initial iterations. use the --benchmark_min_warmup_time CLI option or the MinWarmUpTime on the benchmark function. default is no warmup.

BENCHMARK(BM_StringCreation)->MinTime(2.0)->MinWarmUpTime(1);

The benchmark::State object
===========================
The most important object in google benchmark. Let's see how we can use it.

passing arguments
------------------
You can pass arguments to your benchmark function using this object. Example:

static void myBMFunction(benchmark::State& s) {

}

BENCHMARK(myBMFunction)->Arg(10); // to pass a single argument to your function

BENCHMARK(myBMFunction)->Args({1, 2, 3, 4, 5}); // to pass multiple argument to your function.

BENCHMARK(myBMFunction)->RangeMultiplier(16)->Range(8, 1<<15); // to pass a range of arguments between min, max with geometrically increasing step. min is 8, max is 1<<15 (i.e. 32768), multiplier is 16. so arguments will be 8, 128, 2048, 32768. Default for RangeMultiplier is 8. You can specify Range() multiple times.

BENCHMARK(myBMFunction)->Ranges({ {8, 32}, {16, 64} }); // to pass multiple ranges. your BM function will be called for some appropriately chosen Cartesian products of these two ranges, maybe 2 runs, with arguments: (8, 16), (32, 64). May be 3 runs with some other argument pairs.

If you want every Cartesian product to be generated and benched, you should use ArgsProduct instead of Ranges.
BENCHMARK(myBMFunction)->ArgsProduct({ {8, 32}, {16, 64} });

BENCHMARK(BM_SetInsert)
    ->ArgsProduct({
      benchmark::CreateRange(8, 128, /*multi=*/2), // Helper methods for generating range arguments
      benchmark::CreateDenseRange(1, 4, /*step=*/1) // Helper methods for generating range arguments
    })

BENCHMARK(myBMFunction)->DenseRange(10, 50, 5); // will call your function multiple times, with arguments, 10, 15, 20, 25, 20, 35, 40, 45, 50.

BENCHMARK(myBMFunction)->DenseRange(1, 3, 1)->DenseRange(10, 30, 10); // multiple DenseRanges will result in Cartesian product. your BM function is called with args: (1, 10), (1, 20), (1, 30), (2, 10), (2, 20), (2, 30), (3, 10), (3, 20), (3, 30)

CustomArguments can also be applied:
static void CustomArguments(benchmark::internal::Benchmark* b) {
  for (int i = 0; i <= 10; ++i)
    for (int j = 32; j <= 1024*1024; j *= 8)
      b->Args({i, j});
}
BENCHMARK(myBMFunction)->Apply(CustomArguments);

The final way of capturing arguments is to use BENCHMARK_CAPTURE macro.

template <typename... Args>
void myBMFunction(benchmark::State& state, Args&&... args) {
  auto args_tuple = std::make_tuple(std::forward<Args>(args)...);
  for(auto _ : state) {
      ...
  }
}

BENCHMARK_CAPTURE(myBMFunction, myTestCaseName, Arg1, Arg2, Arg3...)

If you have a BM function which itself is templated and also accepts arguments, then you need to use the
BENCHMARK_TEMPLATE1_CAPTURE(myBMFunction, TemplateArgument, myBMTestName, Arg1); OR
BENCHMARK_TEMPLATE2_CAPTURE(myBMFunction, TemplateArgument, myBMTestName, Arg1, Arg2); // if there are two arguments

Inside your BM function, you can access arguments using state.range(0), state.range(1), state.range(2) and so on.


Setting Labels
---------------
By default, google benchmark will suffix your test case with the arguments. But you can also set your own Label for the test case using SetLabel(string) function. Example:
 int rows = state.range(0);
 int cols = state.range(1);
 // Custom human-readable label
 state.SetLabel("Rows=" + std::to_string(rows) + ", Cols=" + std::to_string(cols));


Parallelism in benchmarks
-------------------------
By default, benchmark only runs 1 thread for your BM function, and all iterations are run in that one thread. You can tell benchmark to run separate threads though using the Threads(10) function. Example:
BENCHMARK(myBMFunction)->Threads(4); // runs 4 threads or using ./bench --benchmark_threads=16

* The framework will launch 4 threads running your benchmark function in parallel.
* Each thread gets its own benchmark::State object.
* You can coordinate across threads if needed (e.g., benchmark a mutex).

you can also give it a range of threads, using ThreadRange(1, 8).
BENCHMARK(myBMFunction)->ThreadRange(1, 8); // will run for 1, 2, 4, 8 threads (i.e. powers of two)

you can also run each thread on separate cpu
BENCHMARK(myBMFunction)->ThreadPerCpu();

Important distinction:
Iterations: how many times the benchmarked code is executed inside the measurement loop. This is about statistical stability.

Threads: how many copies of the benchmark function run concurrently. This is about scalability and contention.
Usually you would want to have multiple threads when you want to test scalability and contention.

Reporting throughput
--------------------
To really test the throughput of your function, we can set additional information on the State object.

SetItemsProcessed(count) --> Report how many items you processed. Throughput = ItemsProcessed/time. Example:
static void BM_Sort(benchmark::State& state) {
    int n = state.range(0);
    std::vector<int> data(n);
    // Initialize data
    for(auto _ : state) {
        std::vector<int> tmp = data;
        std::sort(begin(tmp), end(tmp));
    }
    state.SetItemsProcessed((int64_t)state.iterations() * (int64_t)n); // n elements sorted in each iteration.
}

SetBytesProcessed(count) --> Report how many bytes were processed. Often used in memcpy, I/O, compression benchmarks
static void BM_Memcpy(benchmark::State& state) {
    int n = state.range(0);
    char* src = new char[n];
    char* dst = new char[n];
    for (auto _ : state) {
        memcpy(dst, src, n);
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(n));
    delete[] src;
    delete[] dst;
}

Custom metrics
---------------
You can also include custom metrics using the state.counters variables. "counters" is a public member of type:
std::map<std::string, Counter> UserCounters; so you can set it directly. Key is some string and value is an object of Counter class. Very trivial. you can check yourself in benchmark.h. Example use:

state.counters["throughput"] = benchmark::Counter(
    double(total_ops), benchmark::Counter::kIsRate);

Custom Context
--------------
You can add custom context using "AddCustomContext(string key, string value)". It will show up in the context output.
you can also add context using CLI option --benchmark_context=hostname=$(hostname -f)

SetUp/TearDown
--------------
SetUp/TearDown are run for each repetition of your BM function. Default is 10 so it will be run 10 times. The repetition could be due to
1. benchmark just trying to get a statistically stable result.
2. each run that is triggered for each input parameter.
3. each run that is triggered on a separate thread (based on your Threads(), or ThreadRange() arguments)

Pausing/Resuming
-----------------
If inside your measurement loop, you have some code that should not be benchmarked, you can use PauseTiming() and ResumeTiming() function.

for (auto _ : state) {
    state.PauseTiming();
    data = ConstructRandomSet(state.range(0));
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j)
      data.insert(RandomNumber());
  }

DoNotOptimize/ClobberMemory
---------------------------
DoNotOptimize(x) tells the compiler: “I’m using this value, don’t optimize it away”. It prevents the compiler from eliminating code that produces x because it thinks the result isn’t used. Without this, your benchmark loop might disappear entirely if the compiler realizes it has no observable effect. It also acts as a memory barrier. Basically, it forces the compiler to flush pending writes to memory and reload any other values as necessary.

ClobberMemory() forces the compiler to perform all pending writes to global memory. Useful when you want to benchmark code that reads/writes memory, ensuring previous writes are not optimized away or cached. Example:
    int src[1024];
    int dest[1024];
    for (auto _ : state) {
        memcpy(dest, src, sizeof(src)); //we want this write operation to happen so we call ClobberMemory.
        benchmark::ClobberMemory();  // ensures memcpy actually writes to memory
    }

Another example:
for (auto _ : state) {
    std::vector<int> v;
    v.reserve(1);
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    v.push_back(42); // we want this write to go through.
    benchmark::ClobberMemory(); // Force 42 to be written to memory.
  }

Templated Benchmark functions
-----------------------------
Templated benchmark functions are also allowed. Example:
template <class Q>
static void BM_Sequential(benchmark::State& state) {
  Q q;
  typename Q::value_type v;
  for (auto _ : state) {
    for (int i = state.range(0); i--; )
      q.push(v);
    for (int e = state.range(0); e--; )
      q.Wait(&v);
  }
  // actually messages, not bytes:
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations())*state.range(0));
}

BENCHMARK(BM_Sequential<WaitQueue<int>>)->Range(1<<0, 1<<10);

Fixtures
---------
Benchmark Fixture classes are also supported. Refer to the user guide on github.