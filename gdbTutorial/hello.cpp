#include <iostream>
#include <string>
#include <thread>

using namespace std;

struct hello {
    void operator() () {
        cout << "Hello world from thread: " << std::this_thread::get_id() << endl;
    }
};

int main(int argc, char* argv[]) {
    auto t = std::thread(hello());
    t.join();
    cout << "Goodbye Cruel world from main: " << std::this_thread::get_id() << endl;
    return 0;
}


