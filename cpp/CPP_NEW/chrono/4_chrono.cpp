#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;



int main() {
    auto t1 = std::chrono::high_resolution_clock::now(); // t1 is time_point
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto t2 = std::chrono::high_resolution_clock::now(); // t2 is time_point

    // get difference between t1 and t2, duration_cast is needed
    // Rep is same, but source is nano, and dest is milli so its needed.
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);

    // duration cast not needed here as destination Rep is double which is wider than source Rep.
    std::chrono::duration<double, std::milli> fp_ms = t2-t1;
 
    cout << "int_ms: " << int_ms.count() << endl;
    cout << "fp_ms: " << fp_ms.count() << endl;

    return 0;
}
