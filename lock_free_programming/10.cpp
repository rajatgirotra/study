volatile int value = 0;
volatile int ready = 0;

void sendMessage(int i)
{
    value = i * (i + 6) + 1;
    ready = 1;
}

int revcMessage()
{
    while(!ready);
    int x = value;
    return x;
}

/*
 * Please do g++-4.8.2 -S -O2 -std=c++11 -masm=intel 10.cpp
 */

/*
 * Problem 1 and Problem 2 are fixed, but you know these are still wrong solutions.
 * You need a memory barrier. But first read 11.cpp which proves the points in 9.cpp and then we'll move on 
 * to a barrier solution
 */
