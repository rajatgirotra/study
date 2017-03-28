#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Usage:\n"; 
        cout << "\t " << argv[0] << " <String> <SearchString>" << endl;
        return -1;
    }

    char* buf = argv[1];
    char* searchString = argv[2];
    int startPos = 0;
   
    for(char* bStr = buf + startPos; bStr != '\0';)
    {
        char* sStr = searchString;
        while( (*bStr != 0) && (*sStr != 0) && (*bStr == *sStr))
        {
            ++bStr;
            ++sStr;
        }
        if(*sStr == '\0')
        {
           cout << "Found at index: " << startPos << endl;
           return startPos;
        }
        else if(*bStr == '\0') 
        {
            cout << "Not found:" << endl;
            return -1;
        }
        ++startPos;
        bStr = buf + startPos;
    }
    return 0;
}
             
