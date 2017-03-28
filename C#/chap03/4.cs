//using the out keyword for output parameters.
/*
In C - style languages, it is common for functions to be able to output more than one value from a single
routine. This is accomplished using output parameters, by assigning the output values to variables
that have been passed to the method by reference. Often, the starting values of the variables that are
passed by reference are unimportant. Those values will be overwritten by the function, which may never
even look at any previous value.
It would be convenient if you could use the same convention in C#. However, C# requires that variables
be initialized with a starting value before they are referenced. Although you could initialize your input
variables with meaningless values before passing them into a function that will fill them with real,
meaningful ones, this practice seems at best needless and at worst confusing. However, there is a way to
short - circuit the C# compiler  s insistence on initial values for input arguments.
You do this with the out keyword. When a method  s input argument is prefixed with out , that method
can be passed a variable that has not been initialized. The variable is passed by reference, so any changes
that the method makes to the variable will persist when control returns from the called method. Again,
you also need to use the out keyword when you call the method, as well as when you define it:
*/

using System;

namespace Wrox.ProCSharp.chap03
{
   class MainEntryPoint
   {
      public static void someFunction(out int i)
      {
         i = -98;
      }

      public static void Main(String[] args)
      {
         int i;
         someFunction(out i); // No initialization of i needed. output parameters are by default passed by reference.
         Console.WriteLine("i is " + i);
         return;
      }
   }
}

