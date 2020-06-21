int value = 0;
volatile int ready = 0;

void sendMessage(int i)
{
    value = i * (i + 6) + 1;
    ready = 1;
}

int recvMessage()
{
    while(!ready);
    int x = value;
    return x;
}

int main() {}
/*
 * Please do g++-4.8.2 -S -O2 -std=c++11 -masm=intel lock_free_29.cpp
 */

/*
 * We see that problem 2 gets solved as revcMessage() reads "ready" from memory on each iteration.
 * But problem 1 still remains.
 *
 * The Standard says that reads and writes to volatile data cannot be re-ordered. This means if you have two or more volatile data.
 * Then their reads and writes should be in program order.
 *
 * But volatile data can be re-ordered across ordinary read-writes; as long as it does not change the observable behavior of an
 * abstract machine.
 * So problem 1 remains.
 *
 * To solve it we really need to change value also to volatile(lock_free_30.cpp proves it). But let say value is a complex data structure, then do we keep
 * changing every field in the data structure to volatile. NO ??
 * Really what we need is a memory barrier. To make sure that changes to ready are visible only after value is updated.
 *
 * infact in problem 2 also, there is nothing which prevents the compiler from loading value before loading ready. So we should use
 * memory barrier there also, and get rid of volatile all together.
 *
 * Also ready should be made atomic.
 */
