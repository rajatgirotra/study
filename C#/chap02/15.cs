using System;

namespace Wrox.ProCSharp.Basics
{
   class MainEntryPoint
   {
      public static void Main(String[] args)
      {
         int i = 220;
         int j = 30;
         Console.WriteLine("{0} + {1} equals {2}" , i, j, i+j);

         Console.WriteLine("{0,5}\n +{1,3}\n ----\n{2,5}", i, j, i+j);
         return;
      }
   }
}

  
