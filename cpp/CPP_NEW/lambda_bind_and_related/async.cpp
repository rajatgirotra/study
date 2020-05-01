/*
 * using std::async here
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <future>
using namespace std;

#define WAIT_TIME 2

//Normal Function
int func(int arg) {
   std::this_thread::sleep_for(std::chrono::seconds(WAIT_TIME)); 
   cout << "int func(int arg) called" << endl;
   return arg;
}

//function pointer
int(*poFunc)(int) = 0;

//function object
struct X
{
    void operator()() {
        std::this_thread::sleep_for(std::chrono::seconds(WAIT_TIME)); 
        cout <<"Function object X::operator()() called" << endl;
    }

    double memFunc(bool b) {
        std::this_thread::sleep_for(std::chrono::seconds(WAIT_TIME)); 
        cout <<"Function  double X::memFunc(bool) called" << endl;
        return b;
    }
};

//lambda function
auto l = [] (int x, int y) {
     std::this_thread::sleep_for(std::chrono::seconds(WAIT_TIME)); 
     cout << "Lambda function l called with X: " << x << "   Y: " <<  y << endl;
 };

double(X::*poMemFunc)(bool) = 0;


int main()
{
    X x;
    std::shared_ptr<X> spX(new X());
    X* poX = new X();

    poFunc = &func;

    auto fut = std::async(std::launch::async, func, 10); //bind function
    auto fut_2 = std::async(poFunc, 20); //bind function pointer
    auto fut_3 = std::async(X()); //bind function object

    auto fut_4 = std::async(&X::memFunc, x, true); //bind member function with simple object
    auto fut_5 = std::async(&X::memFunc, poX, true); //or with simple object pointer
    auto fut_6 = std::async(&X::memFunc, spX, true); //or with shared_ptr

    poMemFunc = &X::memFunc;
    auto fut_7 = std::async(poMemFunc, x, false); //bind member function pointer with simple object
    auto fut_8 = std::async(poMemFunc, poX, false); //or with simple object pointer
    auto fut_9 = std::async(poMemFunc, spX, false); //or with shared_ptr

    auto fut_10 = std::async(l, 0, 1); //bind lambda
    //Main should sleep so that all threads created by async can complete.
    std::this_thread::sleep_for(std::chrono::seconds(20)); 
    delete poX;
    return 0;
}

/*
 * Explanation. First see the differences from bind_1.cpp. async is very similar to std::bind in what its arguments are.
 * 1) include <future> header for async.
 * 2) You dont need the round brackets like you do when calling std::bind
 * 3) The async() provides a second c'tor argument which take a launch policy.
 *
 * std::launch::async -  meaning run the thread now.
 * std::launch::deferred - meaning run the thread later when someone tries to get the result of the function call using future.get()
 * std::launch::async |  std::launch::deferred - meaning implementation specific. Run at some point. 
 *
 * Default is "std::launch::async |  std::launch::deferred"
 *
 * So unless we add std::launch::async in all calls above, the functions may or may not run by the time main ends.
 *
 * Also it is possible to get the result of async calls using std::future.get() but we will discuss it later during std multithreading.
 * Also compile it using -lpthread, otherwise you get an runtime exception.
 */
