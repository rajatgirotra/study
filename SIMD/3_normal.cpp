#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

void normal_sqrt(float* a, int N)
{
    for(int i = 0; i < N; ++i)
        a[i] = sqrt(a[i]);
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

    normal_sqrt(a, N);

    cout << a[0] << endl;
    free(a);
    return 0;
}

//Compile using
// g++ -std=c++11 -O3 3_normal.cpp -o normal