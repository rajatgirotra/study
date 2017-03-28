#include <iostream>
using namespace std;

int partition(int arr[], int p, int r)
{
    int i = p-1;
    int j = p;
    int pivot = arr[r];
    while(j < r)
    {
       if(pivot > arr[j])
       {
           i++;
           int tmp = arr[i];
           arr[i] = arr[j];
           arr[j] = tmp;
       }
       j++;
    }
    arr[r] = arr[i+1];
    arr[i+1] = pivot;
    return i+1;
}

void qs(int arr[], int p, int r)
{
   if (p < r)
   {
       int q = partition(arr, p, r);
       qs(arr, p, q-1);
       qs(arr, q+1, r);
   }
}

int main()
{
    int arr[] = {12, 98, 23, 0, -13, 134, 57823, -42342, 323 };
    qs(arr, 0, 8);

    for(int i = 0; i < 9; ++i)
    cout << arr[i] << endl;

    return 0;
}
