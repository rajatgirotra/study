/*
If you want a nonexecutable file (such as a DLL) to be loadable by the .NET runtime, you must compile
it as a library. If you compile a C# file as a module, no assembly will be created. Although modules
cannot be loaded by the runtime, they can be compiled into another manifest using the /addmodule
switch.
Another option we need to mention is /out . This allows you to specify the name of the output file
produced by the compiler. If the /out option isn  t specified, the compiler will base the name of the output
file on the name of the input C# file, adding an extension according to the target type (for example, exe
for a Windows or console application or dll for a class library). Note that the /out and /t , or /target ,
options must precede the name of the file you want to compile.

If you want to reference types in assemblies that aren  t referenced by default, you can use the
/reference or /r switch, together with the path and file name of the assembly. The following
example demonstrates how you can compile a class library and then reference that library in another
assembly. It consists of two files:

 The class library
 A console application, which will call a class in the library

The first file is called MathLibrary.cs and contains the code for your DLL. To keep things simple, it
contains just one (public) class, MathLib , with a single method that adds two int's:
*/

using System;

namespace Wrox.ProCSharp.Basics
{
   // Math Library
   ///<summary>
   /// Wrox.ProCSharp.Basics class
   /// provides a method to add 2 integers
   ///</summary>
   public class MathLib
   {
      ///<summary>
      ///This method adds 2 integers passed as arguments.
      ///</summary>
      ///<returns>Returns an integer equal to the sum of the two passed integers</returns>
      ///<param name="x">Fisrt number to add</param>
      ///<param name="y">Second number to add</param>
      public int addInts(int x, int y)
      {
         return (x+y);
      }
   }
}

/* Read this later -- When you are done with the actual 13.cs and 14.cs example of how to build .NET dll.

The C# compiler can extract the XML elements from the special comments and use them to generate an
XML file. To get the compiler to generate the XML documentation for an assembly, you specify the /doc
option when you compile, together with the name of the file you want to be created:
csc /t:library /doc:Math.xml Math.cs
The compiler will throw an error if the XML comments do not result in a well - formed XML document.
This will generate an XML file named Math.xml , which looks like this:
< ?xml version=1.0? >
< doc >
< assembly >
< name > Math < /name >
< /assembly >
< members >
< member name=T:Wrox.ProCSharp.Basics.Math >
< summary >
Wrox.ProCSharp.Basics.Math class.
Provides a method to add two integers.
< /summary >
< /member >
< member name=
M:Wrox.ProCSharp.Basics.Math.Add(System.Int32,System.Int32) >
< summary >
The Add method allows us to add two integers.
< /summary >
< returns > Result of the addition (int) < /returns >
< param name=x > First number to add < /param >
< param name=y > Second number to add < /param >
< /member >
< /members >
< /doc >
Notice how the compiler has actually done some work for you; it has created an < assembly > element
and also added a < member > element for each type or member of a type in the file. Each < member >
element has a name attribute with the full name of the member as its value, prefixed by a letter that
indicates whether this is a type ( T: ), field ( F: ), or member ( M: ).

*/
