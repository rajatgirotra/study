//Method Overloading
/*
   Method Overloading
   C# supports method overloading  several versions of the method that have different signatures (that
   is, the same name, but a different number of parameters and or different parameter data types).
   However, C# does not support default parameters in the way that, say, C++ or Visual Basic does. In
   order to overload methods, you simply declare the methods with the same name but different numbers
   or types of parameters:
 */

using System;
namespace Wrox.ProCSharp.chap03
{
  class MainEntryPoint
  {
    public static void ShowResult(string result)
    {
      Console.WriteLine("Result String is: " + result);
    }

    public static void ShowResult(int result)
    {
      Console.WriteLine("Result code is: " + result);
    }

    public static void Main()
    {
      ShowResult("The test case did not pass.");
      ShowResult(7);
      return;
    }
  }
}

/*
   Because C# does not support optional parameters, you will need to use method overloading to achieve
   the same effect:

   class MyClass
   {
     int DoSomething(int x) // want 2nd parameter with default value 10
     {
       DoSomething(x, 10);
     }
     int DoSomething(int x, int y)
     {
        //implementation
     }
   }

C# does place some minimum differences on the parameters of overloaded methods:

 It is not sufficient for two methods to differ only in their return type.
 It is not sufficient for two methods to differ only by virtue of a parameter having been declared as ref or out .

 */
