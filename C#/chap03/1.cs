//Learn how to write a simple C# class

using System;

namespace Wrox.ProCSharp.MathTestExample
{
   class MathTest
   {
      public int value;

      public int GetSquare()
      {
         return value*value;
      }

      public static int GetSquareOf(int x)
      {
         return x*x;
      }

      public static double GetPi()
      {
         return 3.14159;
      }
   }

   class MainEntryPoint
   {
      public static void Main(String[] args)
      {
         Console.WriteLine("8 squared is " + MathTest.GetSquareOf(8));

         Console.WriteLine("The value of pi is " + MathTest.GetPi());

         MathTest obj = new MathTest();
         obj.value = 30;

         Console.WriteLine("obj squared is " + obj.GetSquare());
       
         return;
      }
   }
}

