#include "algos.hpp"
#include <iostream>
#include <functional>
using namespace std;

bool isEven(int x)
{
    return ( x%2 == 0);
}

bool isTwo(int x)
{
   return ( x==2 ? true : false); 
}

int main()
{
    int arr[] = {1, 2, 3, 5, 5 };
    int* end = arr + sizeof(arr)/sizeof(arr[0]);
    int* pos = my_adjacent_find(arr, end);
    if (pos == end)
        cout << "No adjacent elements";
    else
        cout << "Adjacent element: " << *pos << endl;


    int alleven[] = {0, 2, 4, 6, 8, 10};
    cout << "my_all_of (even): " << my_all_of(alleven, alleven + sizeof(alleven)/sizeof(alleven[0]), &isEven) << endl;

    int oneeven[] = {1, 3, 5, 7, 9, 10};
    cout << "my_any_of: " << my_any_of(oneeven, oneeven + sizeof(oneeven)/sizeof(oneeven[0]), &isEven) << endl;

    int copyN[] = {1, 3, 5, 7, 9, 10};
    int copyNArr[10] = { 0 };
    int *p = copyNArr;
    cout << "my_copy_n: " << endl;
    for(int i = 0; i < 10; ++i)
        cout << "copyNArr[i]: " << copyNArr[i] << "  ";
    cout << endl;

    int copy[] = {1, 3, 5, 7, 9, 10};
    int *copyArr = (copy - 3);
    cout << "my_copy: "  << endl;
    my_copy(copy, copy+(sizeof(copy)/sizeof(copy[0])), copyArr);
    for(int i = 0; i < 9; ++i)
        cout << "copyArr[i]: " << copyArr[i] << "  ";
    cout << endl;

    int copyB[] = {1, 3, 5, 7, 9, 10};
    int *copyArrB = (copyB + 8);
    cout << "my_copy_backward: "  << endl;
    my_copy_backward(copyB, copyB+(sizeof(copyB)/sizeof(copyB[0])), copyArrB+1);
    for(int i = 0; i < 9; ++i)
        cout << "copyB[i]: " << copyB[i] << "  ";
    cout << endl;

    // remove test
    int remArr[] = {1, 2, 3, 2, 5 , 2};
    int * newEnd = my_remove(remArr, remArr + sizeof(remArr)/sizeof(remArr[0]), 2);
    //int * newEnd = my_remove_if(remArr, remArr + sizeof(remArr)/sizeof(remArr[0]), &isTwo);
    for(int i = 0; i < 6; ++i)
        cout << remArr[i] << "   ";
    cout << endl;
    cout << *newEnd << endl;

    int remArr2[] = {1, 2, 3, 2, 5, 2 };
    int copyArr2[6];
    //int * newEnd2 = my_remove_copy(remArr2, remArr2 + sizeof(remArr2)/sizeof(remArr2[0]), copyArr2, 2);
    int * newEnd2 = my_remove_copy_if(remArr2, remArr2 + sizeof(remArr2)/sizeof(remArr2[0]), copyArr2, &isTwo);
    for(int i = 0; i < 6; ++i)
        cout << copyArr2[i] << "   ";
    cout << endl;
    cout << *newEnd2 << endl;

    //reverse test
    int revArr[] = {1, 2, 3, 4, 5, 6 };
    int revCopyArr[6] ;
    my_reverse(revArr, revArr + sizeof(revArr)/sizeof(revArr[0]));
    for(int i = 0; i < 6; ++i)
        cout << revArr[i] << "  ";
    cout << endl;
    my_reverse_copy(revArr, revArr + sizeof(revArr)/sizeof(revArr[0]), revCopyArr);
    for(int i = 0; i < 6; ++i)
        cout << revCopyArr[i] << "  ";
    cout << endl;

    //rotate test
    int rotArr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    //my_rotate(rotArr, rotArr+3, rotArr+8);
    my_rotate2(rotArr, rotArr+3, rotArr+8);
    for(int i = 0; i < 8; ++i)
        cout << rotArr[i] << "  ";
    cout << endl;

    //rotate copy
    int rotArr2[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int rotCopyArr[8];
    my_rotate_copy(rotArr2, rotArr2+3, rotArr2+8, rotCopyArr);
    for(int i = 0; i < 8; ++i)
        cout << rotCopyArr[i] << "  ";
    cout << endl;


    return 0;
}
