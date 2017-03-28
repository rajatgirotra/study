using System;

namespace Wrox.ProCSharp.Basics
{
   public class ScopeTest
   {
      public static int Main(string[] args)
      {
         int j = 10;
         for(int i = 0; i < 10; ++i)
         {
            int j = 30; // Allowed in C++ (name hiding) but not in C#
            Console.WriteLine(j + i);
         }
         return 0;
      }
   }
}

