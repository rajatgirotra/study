/*
 * std::bind and std::async.
 * You already know what boost::bind does, std::bind is similar.
 * std::async() is also same except that the bound function object is called asynchronously.
 *
 * C++11 says that all callable objects can be passed as argument to bind and async. Following are the callable objects according to C++11
 *
 * Normal functions
 * Function Pointers (includes pointers to member functions)
 * Function objects
 * Lambda functions
 */

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

#define WAIT_TIME 2

//Normal Function
int func(int arg) {
   std::this_thread::sleep_for(std::chrono::seconds(WAIT_TIME)); 
   cout << "int func(int arg) called" << endl;
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

    std::bind(func, 10)(); //bind function
    std::bind(poFunc, 20)(); //bind function pointer
    std::bind(X())(); //bind function object

    std::bind(&X::memFunc, x, true)(); //bind member function with simple object
    std::bind(&X::memFunc, poX, true)(); //or with simple object pointer
    std::bind(&X::memFunc, spX, true)(); //or with shared_ptr 

    poMemFunc = &X::memFunc;
    std::bind(poMemFunc, x, false)(); //bind member function pointer with simple object
    std::bind(poMemFunc, poX, false)(); //or with simple object pointer
    std::bind(poMemFunc, spX, false)(); //or with shared_ptr 

    std:bind(l, 0, 1)(); //bind lambda


    delete poX;
    return 0;
}
