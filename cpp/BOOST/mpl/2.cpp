#include <iostream>
using namespace std;

//Function to count the number of bits set in a byte.
unsigned int countSetBits(const char& byte)
{
    int i = 0;
    unsigned int count = 0;
   
    for(i = 0; i < 8; ++i)
    {
        if( (0x01 << i) & byte)
            count++;
    }
    return count;
}

int main()
{
    char byte = 127;
    cout << countSetBits(byte) << endl;
    return 0;
} 


