#include <iostream>
#include <emmintrin.h> //for SSE2
#include <cstdlib>
using namespace std;


//Note the CPU will treat data in XMM registers depending on the type used
//__m128 will make CPU treat data as 4 byte float
//__m128d will make CPU treat data as 8 byte double
//__m128i will make CPU treat data as 4 byte integer, short and char

void sse_sqrt(float* a, int N)
{
    //assume N % 4 == 0
    int nb_iters = N / 4;
    __m128* ptr = (__m128*)a;
	//incrementing ptr by 1 moves it ahead by 128 bits
	//using _mm_store_ps to store results of square root
    for(int i = 0; i < nb_iters; ++i,++ptr,a+=4)
        _mm_store_ps(a, _mm_sqrt_ps(*ptr));
}

int main(int argc, char *argv[])
{
    //Only FYI, to allocate memory on stack which is aligned, use __attribute((aligned)) expression
    //float a[] __attribute__((aligned(16))) = { 64., 65., 66., 196.};

    //Whereas to alloate memory on heap which is aligned use posix_memalign, include stdlib for that
    if(argc != 2)
    {
        cout << "Usage:\ta.out <SizeOfArray>\n";
        return -1;
    }

    int N = atoi(argv[1]);
    float* a{};
    posix_memalign((void**)&a, 16, sizeof(float)*N);

    for(int i = 0; i < N; ++i)
        a[i] = 3141592.65358;

    sse_sqrt(a, N);

    cout << a[0] << endl;
    free(a);
    return 0;
}

//Compile using
// g++ -std=c++11 -O3 3_simd.cpp -o simd