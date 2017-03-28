// Passing variables by value and by reference

using System;

namespace Wrox.ProCSharp.ParameterTestSample
{
   class ParameterTest
   {
      public static void someFunction(int[] intArray, int i)
      {
         i = 100;
         intArray[0] = 100;
         return ;
      }
   }

   class MainEntryPoint
   {
      public static int Main()
      {
         int i = 100;
         int[] ints = {1,2,3,4,5};

         Console.WriteLine("i = " + i);
         Console.WriteLine("ints[0] = " + ints[0]);
         Console.WriteLine("Calling someFunction");
  
         ParameterTest.someFunction(ints, i);

         Console.WriteLine("i = " + i);
         Console.WriteLine("ints[0] = " + ints[0]);
         return 0;
      }
   }
}

