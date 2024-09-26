/*
jthread stop_tokens work very nicely with std::condition_variables.
what if your thread is blocked on a condition_variable and a stop is requested. C++ provides
support for that. let's see.
*/

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <queue>
using namespace std;
using namespace std::literals;

std::queue<string> messagesQ;
std::mutex mtx;
std::condition_variable_any cv; // limitation, must use condition_variable_any only.

int main() {
    // consumer thread
    std::jthread t([](std::stop_token st) {
        while(!st.stop_requested()) {
            string msg{};
            {
                std::unique_lock<std::mutex> lck(mtx);
                if(!cv.wait(lck, st, [&] () {
                    return !messagesQ.empty();
                })) {
                    // if cv.wait() return false, it means a stop was requested.
                    cout << "Stop requested\n";
                    return;
                }

                // you have the lck now. consume for Q now.
                msg = messagesQ.front();
                messagesQ.pop();
                cout << "Msg: " << msg << endl;
            }
        } 
    });

    // producer
    std::string msg[] = {"Tic", "Tac", "Toe"};
    for(auto&& s : msg) {
        std::scoped_lock lck(mtx);
        messagesQ.push(s);
        cv.notify_one();
    }

    std::this_thread::sleep_for(1s);
    {
        std::scoped_lock lck{mtx};
        messagesQ.push("done");
        cv.notify_all();
    }

    std::this_thread::sleep_for(1s); // wait for 1 sec
}