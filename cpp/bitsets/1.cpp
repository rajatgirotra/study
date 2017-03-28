/* Constructing bitsets */
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
   bitset<10> first;  /* An empty bitset */
   cout<<"first = "<<first<<endl;

   bitset<6> second(12);  /* Initialize with 63; bits are stored from right to left */
   cout<<"second = "<<second<<endl;

   bitset<2> third(string("0101010111")); /* Initialize with this string. Bits are stored from left to right; string should only contain */
                                       /* 0's and 1's; else u'll see a crash */
   cout<<"third = "<<third<<endl;

   bitset<10> fourth(string ("00110101001110"), 3);  /* 101 */
   cout<<"fourth = "<<fourth<<endl;   

   return 0;
}
