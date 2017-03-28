//using System.String

using System;

namespace  Wrox.ProCSharp.Basics
{
   class Program
   {
      static void Main(String[] args)
      {
         String s1 = "Hello World";
         String s2 = s1;
         Console.WriteLine("s1 = " + s1);
         Console.WriteLine("s2 = " + s2);
         s1 = "Good Bye.. Cruel World";
         Console.WriteLine("s1 = " + s1);
         Console.WriteLine("s2 = " + s2);

         string s3 = @"C:\Desktop\First.cs";
         Console.WriteLine(s3);

         string s4 = @"First Line
Second Line";
         Console.WriteLine(s4);

         Console.WriteLine(s4.Length);
         
         return;
      }
   }
}


