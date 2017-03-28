/* Counting sort = O(n) */
#include <iostream>
#include <cstring>
using namespace std;

void counting_sort(int a[], int size, const int max_element)
{
    //Create an array of size max_element + 1
    int b[max_element+1];
    //initialise the array to 0.
    for(int i = 0; i< (max_element+1); ++i)
        b[i] = 0;
    //Record the number of times each element is ocurring in the list
    for(int i = 0; i < size; ++i)
        ++b[a[i]] ;
    //Now record at each index the no of elements that are less than or equal to that index.
    b[0]--;
    for(int i = 1; i< (max_element+1); ++i)
        b[i] = b[i-1] + b[i];

    //Now create another resultant array and store the results in it.
    int c[size];
    for(int i = size-1; i >= 0; --i)
    {
        c[b[a[i]]] = a[i];
        b[a[i]]--; 
    }

    for(int i = 0; i < size; ++i)
        cout << c[i] << "  " ;
    cout << endl;
}

int main()
{
    int a[] = {2, 3, 1, 0, 2, 5, 3, 4, 5, 2, 0, 1, 3 };
    counting_sort(a, 13, 5);
    return 0;
}
