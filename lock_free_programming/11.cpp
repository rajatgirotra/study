volatile int a;
volatile int b;

volatile int x;
int y, z;

void foo()
{
a = 1;
b = 2;
a = 3;
b = 4;
}

void bar(int i)
{
y = 1;
x = 1;
z = y * (3+i);
x = 3;
}
