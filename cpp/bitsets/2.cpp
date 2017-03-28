/*
bitset::set

bitset<N>& set ( );
bitset<N>& set ( size_t pos, bool val = true );

	

Set bits

The version with no parameters sets (to 1) all the bits in the bitset.
The parameterized version, stores val as the new value for bit at position pos.

Parameters

pos
    Order position of the bit whose value is modified.
    Order positions are counted from the rightmost bit, which is order position 0.
    size_t is an unsigned integral type.
val
    Value to store in the bit (either true or false).

Return value
*this

If pos is not a valid bit position, out_of_range is thrown.

*/

#include <iostream>
#include <bitset>

using namespace std;

int main()
{
   bitset<7> mybits;  // 0000
   cout<<"mybits initially = "<<mybits<<endl;

   mybits.set();      // 1111
   cout<<"mybits = "<<mybits<<endl;

   mybits.reset();
   cout<<"mybits reset = "<<mybits<<endl;
 
   mybits.set(2); /* Count ftom right to left, start with zero index.*/
   cout<<"mybits(2) gives = "<<mybits<<endl;

   mybits.set(2, 0);
   cout<<"mybits(2, 0) gives = "<<mybits<<endl;

   return 0;
}
