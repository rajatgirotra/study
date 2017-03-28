/*
The examples so far have shown only the Main() method without any parameters. However, when the
program is invoked, you can get the CLR to pass any command - line arguments to the program by
including a parameter. This parameter is a string array, traditionally called args (although C# will accept
any name). The program can use this array to access any options passed through the command line
when the program is started.
The following sample, ArgsExample.cs , loops through the string array passed in to the Main() method
and writes the value of each option to the console window:
*/

using System;
namespace Wrox.ProCSharp.Basics
{
   class ArgsExample
   {
      public static int Main(string[] args)
      {
         for (int i = 0; i < args.Length; i++)
         {
            Console.WriteLine("Argument " + i + " is: " +  args[i]);
         }
         return 0;
      }
   }
}

/* 
I executed 12.exe like this:
$ 12.exe "'Rajat Girotra'" '"Roopak Girotra"'
'Rajat Girotra'
"Roopak Girotra"

Note the argument quoting is similar to XML attribute qouting
*/

