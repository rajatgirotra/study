//using C# structs

using System;
namespace Wrox.ProCSharp.chap03
{
   struct FurnitureSize
   {
      double Length;
      double Width;
   
      public FurnitureSize(double length, double width)
      {
         Length = length;
         Width = width;
      }

      public double Diagnol
      {
         get
         {
            return Math.Sqrt(Length*Length + Width*Width);
         }
      }
   }

   class MainEntryPoint
   {
      public static void Main()
      {
         FurnitureSize obj = new FurnitureSize(12,5);
         Console.WriteLine("Diagnol is: " + obj.Diagnol);
         return;
      }
   }
}

/*
Although structs are value types, you can often treat them syntactically in the same way as classes. For
example, with the definition of the Dimensions class in the previous section, you could write:

Dimensions point = new Dimensions();
point.Length = 3;
point.Width = 6;

Note that because structs are value types, the new operator does not work in the same way as it does for
classes and other reference types. Instead of allocating memory on the heap, the new operator simply
calls the appropriate constructor, according to the parameters passed to it, initializing all fields. Indeed,
for structs it is perfectly legal to write:

Dimensions point;
point.Length = 3;
point.Width = 6;

Structs and Inheritance

Structs are not designed for inheritance. This means that it is not possible to inherit from a struct. The
only exception to this is that structs, in common with every other type in C#, derive ultimately from the
class System.Object . Hence, structs also have access to the methods of System.Object , and it is even
possible to override them in structs  an obvious example would be overriding the ToString()
method. The actual inheritance chain for structs is that each struct derives from a class, System
.ValueType , which in turn derives from System.Object . ValueType does not add any new members
to Object , but provides implementations of some of them that are more suitable for structs. Note that
you cannot supply a different base class for a struct: every struct is derived from ValueType .

Constructors for Structs

You can define constructors for structs in exactly the same way that you can for classes, except that you
are not permitted to define a constructor that takes no parameters. This may seem nonsensical, and the
reason is buried in the implementation of the .NET runtime. Some rare circumstances exist in which the
.NET runtime would not be able to call a custom zero - parameter constructor that you have supplied.
Microsoft has therefore taken the easy way out and banned zero - parameter constructors for structs in C#.
That said, the default constructor, which initializes all fields to zero values, is always present implicitly,
even if you supply other constructors that take parameters. Its also impossible to circumvent the default
constructor by supplying initial values for fields. The following code will cause a compile - time error:
struct Dimensions
{
   public double Length = 1; // error. Initial values not allowed
   public double Width = 2; // error. Initial values not allowed
}
*/
