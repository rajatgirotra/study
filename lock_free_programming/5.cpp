 int A;
 volatile int B;

void foo()
{
    A = B + 1;
    B = 0;
}

