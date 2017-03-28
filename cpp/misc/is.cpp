#include <iostream>
using namespace std;

void is(int arr[], int size)
{
    //Insertion sort.
    for(int i = 1; i<size; ++i)
    {
        int tmp = arr[i];
        int j = i-1;
        while(j>=0 && (arr[j] > tmp))
        {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = tmp;
    }
}

int main()
{
    int arr[] = {12, 98, 23, 0, -13, 134, 57823, -42342, 323 };
    is(arr, 9);

    for(int i = 0; i < 9; ++i)
    cout << arr[i] << endl;

    return 0;
}
