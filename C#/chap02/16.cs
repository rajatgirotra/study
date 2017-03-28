//using format strings with Console.WriteLine()
using System;

namespace Wrox.ProCSharp.Basics
{
   class MainEntryPoint
   {
      public static void Main(String[] args)
      {
         decimal i = 234.789m;
         int  j = 234;
         Console.WriteLine("{0,9:C2}", i);
         Console.WriteLine("{0,9:P2}", i);
         Console.WriteLine("{0,9:X}", j);
         return;
      }
   }
}
 

