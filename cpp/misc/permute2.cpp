#include <iostream>
using namespace std;

int swaps = 0;
void swap(char* x, char* y)
{
    ++swaps;
    char t = *x;
    *x = *y;
    *y = t;
}

int count = 0;
void per(const char* s, char* x)
{
    ++count;
    if(*x == 0)
    { cout << s << endl; return;}

    per(s, (x+1));
    char* y = x+1;
    while(*y != 0)
    {
        swap(x, y);
        per(s, (x+1));
        swap(x, y);
        y++;
    }
}

int main()
{
    char buf[] = "ABCD";
    per(buf, buf);
    cout << "Count " << count << endl;
    cout << "Swaps " << swaps << endl;
    return 0;
}

