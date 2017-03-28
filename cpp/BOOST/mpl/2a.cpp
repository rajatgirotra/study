#include <iostream>
using namespace std;

template <typename T>
int countSetBits(const T& value)
{
    int count = 0;
    for(int i = 0; i < sizeof(T)*8; ++i) //8 bits per byte
    {
        if((0x01 << i) & value)
            ++count;
    }
    return count;
}

int main()
{
    cout << countSetBits(10) << endl;
    cout << countSetBits('C') << endl;

    return 0;
}

        
