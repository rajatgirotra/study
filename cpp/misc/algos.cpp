#include "algos.hpp"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <iomanip>
#include <set>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int binarySearch(const boost::shared_ptr<Details> arr[], const Details& key, int lowerBound, int upperBound)
{
    int mid = -1;
    bool bFound = false;
    while(lowerBound < upperBound)
    {
        mid = (lowerBound + upperBound)/2;
        if(*arr[mid] == key)
        {
            bFound = true;
            return mid;
        }
        else if(*arr[mid] < key)
            lowerBound = mid + 1;
        else upperBound = mid;
    }
    if(bFound)
        return mid;
    else
        return (-(mid) -1);
}


int binarySearchR(const boost::shared_ptr<Details> arr[], const Details& key, int lowerBound, int upperBound)
{
    if((lowerBound == 0) &&  (upperBound == 0))
        return (-(upperBound) - 1);
    else if(lowerBound >= upperBound)
        return (-(upperBound));
    else
    {
        int mid = (lowerBound + upperBound)/2;
        if(*arr[mid] == key)
            return mid;
        else if(*arr[mid] < key)
            return binarySearchR(arr, key, mid + 1, upperBound);
        else
            return binarySearchR(arr, key, lowerBound, mid);
    }
}

/* Given the array arr, index p,q and r such that
 * [p, q] and [q+1, r] is sorted.
 * Reallign arr[] such that [p, r] is sorted.
 */
void merge(boost::shared_ptr<Details> arr[], int p, int q, int r)
{
    const int n1 = q-p+1;
    const int n2 = r-q;
    boost::shared_ptr<Details> left[n1];
    boost::shared_ptr<Details> right[n2];
    for(int i = 0; i < n1; ++i)
        left[i] = arr[p+i];
    for(int i = 0; i < n2; ++i)
        right[i] = arr[q+1+i];
    int i = 0, j = 0;
    for(int k = p; k <=r; ++k)
    {
        if(i >= n1)
            arr[k] = right[j++];
        else if(j >= n2)
            arr[k] = left[i++];
        else if (*left[i] <= *right[j])
            arr[k] = left[i++];
        else
            arr[k] = right[j++];
    }
}

void mergeSort(boost::shared_ptr<Details> arr[], int p, int r)
{
    if(p < r)
    {
        int q = (p+r)/2;
        mergeSort(arr, p, q);
        mergeSort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}


namespace
{
    string generate_str(const int& characters)
    {
        static string alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string str;
        int i = 0;
        while(i++ < characters)
            str.append(1, alphabets[rand() % alphabets.size()]);
        return str;
    }
    int generate_int(const int& upperBound = 15)
    {
        return (rand() % upperBound);
    }
    double generate_dbl(const double& tmpValue = 67.77)
    {
        double f = (double)(rand() / tmpValue);
        return (f*(67.7 - 12.5) + 12.5);
    }

    struct str_generate
    {
        string operator()()
        {
            return generate_str(7);
        }
    };
}

void printArray(const boost::shared_ptr<Details> arr[])
{
    for(int i = 0; i < 7; ++i)
        cout << *arr[i] << endl;
}


typedef bool (*funcPtr)(const Details&, const Details&);
int main()
{
    srand(time(0));
    cout.precision(6);
    cout.setf(std::ios::fixed);

    boost::shared_ptr<Details> detailsArr[7];
    for(int i = 0; i < 7; ++i)
        detailsArr[i].reset(new Details(generate_str(7), generate_int(), generate_dbl()));
        //detailsArr[i].reset(new Details(generate_str(7), i*7, generate_dbl()));

    printArray(detailsArr);
    cout << endl;
    mergeSort(detailsArr, 0, 6);
    cout <<"After merge sort" << endl;
    printArray(detailsArr);

    Details d1(generate_str(7), generate_int(), generate_dbl());
    int index;
    cout << "\nSearching for\n " << d1 << endl;
    if((index = binarySearchR(detailsArr, d1, 0, 7)) >= 0)
        cout << "Element found at index: " << index << endl;
    else
        cout << "Element not found, but can be inserted at index: " << index << endl;
    return 0;
}
