#include <iostream>
using namespace std;

int MCS(int a[], int size)
{
    int sum, maxSum;
    sum = maxSum = a[0];
    for(int j = 1; j < size; ++j)
    {
        int tmpSum = sum + a[j];    
        sum = (tmpSum > a[j] ? tmpSum : a[j]);

        if(sum > maxSum)
            maxSum = sum;
    }
    return maxSum;
}

int MCS2(int a[], int size)
{
    int tmpSum, maxSum;
    tmpSum = maxSum = a[0];
    for(int i = 1; i < size; ++i)
    {
        tmpSum += a[i];
        if(tmpSum < a[i])
            tmpSum = a[i];
        if(tmpSum > maxSum)
            maxSum = tmpSum;
     }
     return maxSum;
}

int main()
{
    int arr[] = {2, 3, 4, 5, -18, 2, 2 };
    //int arr[] = {-22, 3, 4, 5, -18, 2, 2 };
    //int arr[] = {-11,-2,3,-1,2,-9,-4,-5,-2, -3};
    //int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int size = sizeof(arr)/sizeof(arr[0]);
    cout << MCS(arr, size) << endl;
    cout << MCS2(arr, size) << endl;

    return 0;
}

