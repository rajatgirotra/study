#include <iostream>
#include <string>
#include <locale>
using namespace std;

int main()
{
    std::locale::global(std::locale("en_US.utf8"));
    std::wcout.imbue(std::locale());
    //wstring h = L"\u0930\u093E\u092E";
    wstring h = L"\u0950";
    wcout << sizeof(h) << endl;
    wcout << h << endl;
}
