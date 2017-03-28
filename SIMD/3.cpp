/*
Using C++ intrincics is a really low-level construct as the functions add directly on the 128 bit data (xmm registers).
Some of the data types used in SSE are:

__m128 for float
__m128d for double
__m128i for integer, char and short

This does not mean that if you want to add two float arrays using SSE SIMD, then you have to create arrays of type __m128.
You can create normal float arrays and then easily typecast the array to __m128* (appropriate pointer type) and then use SSE operations.

CAVAET: Most of the SSE operations require data to be 16 byte aligned. So you will see later that we specify an alignment of 16 using the
__attribute__((aligned)) expression provided by gcc.

Lets show you a very simple way of calcuating the square root of 4 floats at once using the SSE Instruction: 
*/

#include <emmintrin.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    float a[] __attribute__((aligned (16))) = {64, 729, 2.0, 10};
    __m128* floatArray = (__m128*)a;
    __m128 t = _mm_sqrt_ps(*floatArray);

    cout << t [0] << endl;
    
}

