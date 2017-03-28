#include <thread>
#include <vector>
#include <iostream>
using namespace std;

struct nothing_thread {
    void operator() () {
        cout << "Doing nothing" << endl;
    }
};

void nothing() {
    cout << "Doing nothing" << endl;
}

int main() {
    vector<thread> v;
    v.push_back(thread(nothing_thread()));
    std::thread t = std::move(v.back());
    t.join();
    v.clear();
    // for (auto& th : v) th.join();
    return 0;
}
