#include <iostream>

using namespace std;

/* Let say the byte is known at compile time.
   Then this can be done at compile time. The compiler will need to generate the template definition for the template
   class and in that process, it will calculate the no. of bits set in that byte. */
template <unsigned char byte>
struct  BIT_SET
{
    enum  
    {
        B0 = ( 0x01 & byte ) ? 1 : 0,
        B1 = ( 0x02 & byte ) ? 1 : 0,
        B2 = ( 0x04 & byte ) ? 1 : 0,
        B3 = ( 0x08 & byte ) ? 1 : 0,
        B4 = ( 0x10 & byte ) ? 1 : 0,
        B5 = ( 0x20 & byte ) ? 1 : 0,
        B6 = ( 0x40 & byte ) ? 1 : 0,
        B7 = ( 0x80 & byte ) ? 1 : 0
    };

    enum { RESULT = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 };
};

int main()
{
    cout << "No. Of bits set in 15: " << BIT_SET<15>::RESULT << endl;
    return 0;
}
