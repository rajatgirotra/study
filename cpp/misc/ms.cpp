#include <iostream>
using namespace std;

/* Arrays arr[p,q] and arr[q+1, r] are sorted.
 * This function sorts arr[p, r]
 */
void merge(int arr[], int p, int q, int r)
{
    int n1 = q-p+1;
    int n2 = r-q;
    int left[n1], right[n2];
    for(int i = 0; i < n1; ++i)
        left[i] = arr[p+i];
    for(int i = 0; i < n2; ++i)
        right[i] = arr[q+1+i];
    int i = 0, j = 0;
    for(int k = p; k <= r; ++k)
    {
        if(i>=n1)
            arr[k] = right[j++];
        else if(j>=n2) 
            arr[k] = left[i++];
        else if(left[i] > right[j])
            arr[k] = right[j++];
        else
            arr[k] = left[i++];
    }
}

void ms(int arr[], int p, int r)
{
   if (p < r)
   {
       int q = (p+r)/2;
       ms(arr, p, q);
       ms(arr, q+1, r);
       merge(arr, p, q, r);
   }
}

int main()
{
    int arr[] = {12, 98, 23, 0, -13, 134, 57823, -42342, 323 };
    ms(arr, 0, 8);

    for(int i = 0; i < 9; ++i)
    cout << arr[i] << endl;

    return 0;
}
