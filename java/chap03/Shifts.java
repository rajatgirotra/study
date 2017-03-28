import java.util.*;

class Shifts
{
   public static void main(String[] args)
   {
      short s = -1;
      System.out.println( s >>>= 10);
      return;
   }
}

/*
The signed right shift >> uses sign extension: if the value is
positive, zeroes are inserted at the higher-order bits; if the value is
negative, ones are inserted at the higher-order bits. Java has also added
the unsigned right shift >>>, which uses zero extension: regardless of the
sign, zeroes are inserted at the higher-order bits. This operator does not
exist in C or C++.

There is a problem,
however, with the unsigned right shift combined with assignment. If you
use it with byte or short you dont get the correct results. Instead, these
are promoted to int and right shifted, but then truncated as they are
assigned back into their variables, so you get -1 in those cases.

So short s = -1;
i.e  in Binary = 0x FF FF FF FF (because it gets promoted to int)
then right shifted 10 bits
===>> i = 0x 00 3F FF FF
Then truncated the high order 16 bits, so you get
i = 0x FF FF
which is -1 in decimal.

*/
