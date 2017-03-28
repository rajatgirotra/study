using System;
namespace Wrox.ProCSharp.Basics
{
   class MainEntryPoint
   {
      static void Main(string[] args)
      {
         // This loop iterates through rows...
         Console.Write(" ");
         for (int i = 0; i < 100; i+=10)
         {
            // This loop iterates through columns...
            for (int j = i; j < i + 10; j++)
            {
               if (j.ToString().Length <= 1)
                  Console.Write("0" + j + " ");
                
               else 
                  Console.Write(" " + j);
            }
            Console.WriteLine();
         }
      }
   }
}

/*
C and C++ programmers should take note of one particular feature of the preceding example. The
counter variable in the innermost loop is effectively redeclared with each successive iteration of the outer
loop. This syntax is legal not only in C# but in C++ as well.
*/
