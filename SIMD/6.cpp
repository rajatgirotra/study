/*
Lets try to use some SSE intrinsic functions
*/

#include <iostream>
#include <emmintrin.h> //SSE2
using namespace std;

int main(int argc, char *argv[])
{
    char ch[16] __attribute__((aligned (16))) {};

    for (int i = 0; i < 16; ++i)
        ch[i] = 'A' + i;

    for (int i = 0; i < 16; ++i)
        cout << ch[i];

    //Zero out all 16 bytes, sp ABCDEFGHIJKLMNOP becomes 0000000000000000
    __m128i* poXMM = (__m128i*)ch;
    *poXMM = _mm_setzero_si128();

    cout << endl;
   for (int i = 0; i < 16; ++i)
       cout << (int)ch[i];


    cout << endl;
    return 0;
}

