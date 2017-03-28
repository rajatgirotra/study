#include <iostream>
using namespace std;

int countPaths(int m[][3], int max_r, int max_c, int r, int c)
{
    if( (r == max_r) && (c == max_c))
        return 1;
    else if(r == max_r)
        return countPaths(m, max_r, max_c, r, c+1);
    else if(c == max_c)
        return countPaths(m, max_r, max_c, r+1, c);
    return countPaths(m, max_r, max_c, r+1, c) + countPaths(m, max_r, max_c, r, c+1); 
}

int countPaths2(int m[][3], int max_r, int max_c, int r, int c)
{
    if((r == max_r) || (c == max_c))
        return 1;
    return countPaths2(m, max_r, max_c, r+1, c) + countPaths2(m, max_r, max_c, r, c+1); 
}

int main()
{
    int a[3][3];
    cout << countPaths(a, 3, 3, 1, 1) << endl;
    cout << countPaths2(a, 3, 3, 1, 1) << endl;
  
    return 0;
}
