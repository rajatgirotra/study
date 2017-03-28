#include <iostream>
using namespace std;

inline int left(int i) { return ( (2*i) + 1 ); }
inline int right(int i) { return ( (2*i) + 2 ); }
inline int parent(int i) { return ( (i-1)/2 ); }

/* 
 * MAX_HEAPIFY(int arr[], int array_size, int heap_size, int index)
 */
void max_heapify(int arr[], int heap_size, int index)
{
    int l = left(index);
    int r = right(index);
    int largest;

    if((l < heap_size) && (arr[l] > arr[index]))
        largest = l;
    else
        largest = index;

    if((r < heap_size) && (arr[r] > arr[largest]))
        largest = r;

    if(largest != index)
    {
        int tmp = arr[index];
        arr[index] = arr[largest];
        arr[largest] = tmp;
        max_heapify(arr, heap_size, largest);
    }
}

void build_max_heap(int arr[], int array_size)
{
    for(int i = array_size/2 - 1; i>=0; --i)
        max_heapify(arr, array_size, i);
}

void hs(int arr[], int array_size)
{
    int heap_size = array_size;
    build_max_heap(arr, array_size);
    for(int i = array_size - 1; i >= 1; --i)
    {
        int tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        heap_size--;
        max_heapify(arr, heap_size, 0);
    }
}

int main()
{
    int arr[] = {12, 98, 23, 0, -13, 134, 57823, -42342, 323 };
    hs(arr, 9);

    for(int i = 0; i < 9; ++i)
    cout << arr[i] << endl;

    return 0;
}
