/*
For example, whereas int represents a single integer, int[] represents an array of integers:

int[] integers;

To initialize the array with specific dimensions, you can use the new keyword, giving the size in the
square brackets after the type name:
// Create a new array of 32 ints.
int[] integers = new int[32];

All arrays are reference types and follow reference semantics. Hence, in this code, even though the
individual elements are primitive value types, the integers array is a reference type. So if you later
write

int [] copy = integers;

this will simply assign the variable copy to refer to the same array  it won  t create a new array.

To access an individual element within the array, you use the usual syntax, placing the index of the
element in square brackets after the name of the array. All C# arrays use zero - based indexing, so you can
reference the first variable with the index zero:

integers[0] = 35;

Similarly, you reference the 32 element value with an index value of 31:

integers[31] = 432;

C#  s array syntax is flexible. In fact, C# allows you to declare arrays without initializing them so that the
array can be dynamically sized later in the program. With this technique, you are basically creating a
null reference and later pointing that reference at a dynamically allocated stretch of memory locations
requested with the new keyword:

int[] integers;
integers = new int[32];

You can find out how many elements are in any array by using this syntax:

int numElements = integers.Length; // integers is any reference to an array.

*/

using System;

namespace Wrox.ProCSharp.Basics
{
   class MainEntryPoint
   {
      public static void Main(String[] args)
      {
         int[] integerArray;
         integerArray = new int[5];
       
         for(int i = 0; i < integerArray.Length; ++i)
            integerArray[i] = (i*10);

         Console.WriteLine(integerArray[3]); // should print 30

         int[] copy = integerArray;
         copy[3] = -1 * copy[3];
 
         Console.WriteLine(integerArray[3]); // should print -30
         Console.WriteLine("Array size = " + copy.Length);
         
         return ;
      }
   }
}

