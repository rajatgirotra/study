#include <iostream>
using namespace std;

int swaps = 0;
void swap (char* x, char* y)
{
    ++swaps;
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

int count = 0;

void permute(char* s, int lb, int ub)
{
    count++;
    int j;
    if(lb == ub)
        cout << s << endl;
    else
    {
        for(int j = lb; j <= ub; ++j)
        {
            swap((s+lb), (s+j));
            permute(s, lb+1, ub);
            swap((s+lb), (s+j));
        }
    }
}

int main()
{
    char a[] = "abcd";
    permute(a, 0, 3);
    cout << "Count " << count << endl;
    cout << "Swaps " << swaps << endl;
    return 0;
}
