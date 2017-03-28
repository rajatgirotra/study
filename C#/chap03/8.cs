//using this to call a c'tor of a class from another c'tor of the same class.
//Crate a class that has an integer field. The value of this integer will be the sum of the two integers passed as
//arguments to the c'tor. If only one integer parameter is passed. The other should be assumed to be zero.

using System;
namespace Wrox.ProCSharp.chap03
{
   class Summation
   {
      private int sum;
      public Summation(int x) : this(x, 0)
      {
         Console.WriteLine("One argument c'tor called.. Sum is: " + sum);
      }

      public Summation(int x, int y)
      {
         sum = x + y;
         Console.WriteLine("Two argument c'tor called.. Sum is: " + sum);
      }
   }

   class SummationTest
   {
      public static void Main()
      {
         Summation obj = new Summation(7);
         Summation obj1 = new Summation(7, 9);
         return;
      }
   }
}

