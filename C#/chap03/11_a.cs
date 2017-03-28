//Using partial classes in C#

using System;
namespace Wrox.ProCSharp.chap03
{
  partial class MyPartialClass
  {
    public static int MethodOne()
    {
       Console.WriteLine("This is MethodOne() of the partial base class.");
       return -1;
    }
    public void bar()
    {
      Console.WriteLine("In MyPartialClass::bar() function,");
    }
  }
}

 
