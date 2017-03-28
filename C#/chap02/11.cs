/*
The Main() Method

As you saw at the start of this chapter, C# programs start execution at a method named Main() .
This must be a static method of a class (or struct), and must have a return type of either int or void .

Although it is common to specify the public modifier explicitly, because by definition the method must
be called from outside the program, it doesn  t actually matter what accessibility level you assign to the
entry - point method  it will run even if you mark the method as private .

Multiple Main() Methods

When a C# console or Windows application is compiled, by default the compiler looks for exactly one
Main() method in any class matching the signature that was just described and makes that class method
the entry point for the program. If there is more than one Main() method, the compiler will return an
error message. For example, consider the following code called MainExample.cs :

using System;
namespace Wrox.ProCSharp.Basics
{
class Client
{
public static int Main()
{
MathExample.Main();
return 0;
}
}
class MathExample
{
static int Add(int x, int y)
{
return x + y;
}
public static int Main()
{
int i = Add(5,10);
Console.WriteLine(i);
return 0;
}
}
}
This contains two classes, both of which have a Main() method. If you try to compile this code in the
usual way, you will get the following errors:
csc MainExample.cs
Microsoft (R) Visual C# Compiler version 9.00.20404
for Microsoft (R) .NET Framework version 3.5
Copyright (C) Microsoft Corporation. All rights reserved.

MainExample.cs(7,23): error CS0017: Program MainExample.exe has more than
one entry point defined: Wrox.ProCSharp.Basics.Client.Main()
MainExample.cs(21,23): error CS0017: Program MainExample.exe has more than
one entry point defined: Wrox.ProCSharp.Basics.MathExample.Main()
However, you can explicitly tell the compiler which of these methods to use as the entry point for the
program by using the /main switch, together with the full name (including namespace) of the class to
which the Main() method belongs:

csc MainExample.cs /main:Wrox.ProCSharp.Basics.MathExample

*/

using System;

namespace Wrox.ProCSharp.Basics
{
   class MainEntryPoint1
   {
      public static void Main(String[] args)
      {
        Console.WriteLine("Wrox.ProCSharp.Basics.MainEntryPoint1 called");
        return;
      }
   }
}

class MainEntryPoint1
{
    public static void Main(String[] args)
    {
      Console.WriteLine("MainEntryPoint1 called");
      return;
    }
}

