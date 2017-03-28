#include <iostream>
using namespace std;

 

int bsHelper(int arr[], int item, int lb, int ub)
{
    while(lb < ub)
    {
        int mid = (lb + ub)/2;
        if(arr[mid] == item)
            return mid;
        else if(arr[mid] > item)
            ub = mid;
        else
            lb = mid + 1;
    }
    return (-lb-1);
}

int bsHelperR(int arr[], int item, int lb, int ub)
{
    if(lb < ub)
    {
        int mid = (lb + ub)/2;
        if(arr[mid] == item)
            return mid;
        else if(arr[mid] > item)
            return bsHelperR(arr, item, lb, mid);
        else
            return bsHelperR(arr, item, mid+1, ub);
    }
    return (-lb-1);
}

int bs(int arr[], int item)
{
    //return bsHelper(arr, item, 0, 6);
    return bsHelperR(arr, item, 0, 6);
}
int main()
{
    int arr[] = { 10, 20, 30, 40, 50, 60 };
    cout << bs(arr, 10) << endl;
    cout << bs(arr, 20) << endl;
    cout << bs(arr, 30) << endl;
    cout << bs(arr, 40) << endl;
    cout << bs(arr, 50) << endl;
    cout << bs(arr, 60) << endl << endl;

    cout <<  bs(arr, 0) << endl;
    cout <<  bs(arr, 15) << endl;
    cout <<  bs(arr, 25) << endl;
    cout <<  bs(arr, 35) << endl;
    cout <<  bs(arr, 45) << endl;
    cout <<  bs(arr, 55) << endl;
    cout <<  bs(arr, 65) << endl;
    return 0;
}
