using System;

namespace Wrox.ProCSharp.Basics
{
   public class ScopeTest
   {
      public static int Main(String[] args)
      {
         for(int i = 0; i < 10; ++i)
            Console.WriteLine(i); // i goes out of scope here

         // more code here..

         for(int i = 10; i > 0; --i)
            Console.WriteLine(i); // i goes out of scope here

         return 0;
      }
   }
}

