#include <iostream>
#include <string>
using namespace std;

string::iterator findSubSeq(string::iterator first1, string::iterator last1, string::iterator first2, string::iterator last2)
{
    while(first1 != last1)
    {
        string::iterator it1 = first1;
        string::iterator it2 = first2;
        while(*it1 == *it2)
        {
            ++it1; ++it2;
            if(it2 == last2) return first1;
            if(it1 == last1) return last1;
        }
        first1++;
    }
    return last1;
}

bool findSubSeq(string source, string seq, int& index)
{
    bool bFound = false;
    string::iterator it = findSubSeq(source.begin(), source.end(), seq.begin(), seq.end());
    if(it != source.end())
    {
        bFound = true;
        index = it - source.begin();
    }
    return bFound;
}
    
    


int main()
{
    string src = "Rajat";
    string seq = "Rajat";

    int index = -1;
    if(findSubSeq(src, seq, index))
        cout << "Substring found at index: " << index << endl;
    else
        cout << "Substring NOT found." << endl;

    return 0;
}
