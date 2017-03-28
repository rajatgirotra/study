/*
 * You can define a raw string using R"( and )"
 */
#include <iostream>
#include <string>
using namespace std;

int main()
{
   string str = R"(This is a quote. " \n is not expanded to new line
                   \ is not an escape character.
                   and this is a single quote'. )";

    string str2 =  R"c(a\
                        b\n"(
                      )c";

    cout <<  str << endl;
    cout <<  str2 << endl;
    return 0;
}
 
/* I still need to understand how using a delimiter
 * R"delim(   )delim" allows you to create a raw string with an embedded (".
 * But we will come to it later, as mostly these raw string are used in regular expressions.
 *
 * Also you can now prefix a string with an encoding prefix like u8 (for utf-8), U (for char32_t),
 * u for char16_t , L for wide character (wchar_t)
 */
