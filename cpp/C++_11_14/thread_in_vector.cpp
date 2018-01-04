#include <thread>
#include <vector>
#include <iostream>
#include <system_error>
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
    try {
        for (auto& th : v) {
            if(th.joinable()) th.join();
        }
    } catch(const std::system_error& e) {
        cout << "Exception: " << e.what() << endl;
    }
    return 0;
}
