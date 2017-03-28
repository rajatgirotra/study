int value = 0;
int ready = 0;

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
 * Please do g++-4.8.2 -S -O2 -std=c++11 -masm=intel 8.cpp
 */

/*
 * See 8.s sendMessage() and recvMessage()
 * Problem 1) in SendMessage ready is set to 1 before value is set. So another thread running on a different core can access value 
 * even when it is not set.
 *
 * Problem 2) in recvMessage() - the compiler optimizes the while loop; making it an infinite loop.
 *
 * Lets try fix both problems by making ready as volatile in 9.cpp
 */
