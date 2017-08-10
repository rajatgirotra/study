/*
We have a simple accumulator function which takes as reference a vector of floats and adds them and returns the result.
We'll the performance of this function on:
1) A single core to form some benchmark
2) Run two instances on different cores
3) Run two instances on the same hyperthreaded code to understand the timing.

each vector has 10 million entries.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <random>
using namespace std;

void accum(const std::vector<double>& dblList, double& result) {
    auto start = std::chrono::steady_clock::now();
    auto res = 0.0;
    for(const auto& item : dblList)
        res += item;
    result = res;
    auto end = std::chrono::steady_clock::now();
    cout << "Duration = " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << "\n";
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(1, 2);	

    constexpr auto count = 10000000;
    std::vector<double> dblList;
    dblList.reserve(count);
    for(auto i = 0; i < count; ++i)
        dblList.push_back(dis(gen));

    double res = 0.;
    accum(dblList, res);
    cout << res << endl;
    return 0;
}
