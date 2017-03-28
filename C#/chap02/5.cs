using System;

namespace Wrox.ProCSharp.Basics
{
   class ScopeTest2
   {
      static int j = 20;
      //Console.WriteLine(j);

      public static void Main()
      {
         int j = 30;
         /**
           * This code will compile, even though you have two variables 
           * named j in scope within the Main() method: the j that was defined at the class level,
           * and doesn  t go out of scope until the class is destroyed (when the Main() method terminates,
           * and the program ends); and the j defined in Main() . In this case,
           * the new variable named j that you declare in the Main() method hides the class - level variable with the
           * same name, so when you run this code, the number 30 will be displayed. 
         */
         Console.WriteLine(j);
         
         string jabberwocky = @"’Twas brillig and the slithy toves
			Did gyre and gimble in the wabe.";
			
	Console.WriteLine(jabberwocky);
         //Console.WriteLine(ScopeTest2.j);
         return ;
      }
   }
}

