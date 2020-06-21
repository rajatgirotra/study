#include "15.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
using namespace std;

ArrayOfItems a(100000);

static std::default_random_engine generator;
static std::uniform_int_distribution<int> distribution(1, 100000);
void setterThread()
{
    for(int i = 0; i < 100000; ++i)
    {
        a.setItem(distribution(generator), distribution(generator));
    }
}

void getterThread()
{
}

int main()
{

    std::thread tg1(getterThread);
    std::thread tg2(getterThread);
    std::thread ts1(setterThread);
    std::thread ts2(setterThread);

    tg1.join(); tg2.join();
    ts1.join(); ts2.join();
    return 0;
}
