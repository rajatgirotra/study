/*
Another use of the using keyword is to assign aliases to classes and namespaces. If you have a very long
namespace name that you want to refer to several times in your code but don  t want to include in a
simple using statement (for example, to avoid type name conflicts), you can assign an alias to the
namespace. The syntax for this is:

using alias = NamespaceName;

The following example (a modified version of the previous example) assigns the alias Introduction to
the Wrox.ProCSharp.Basics namespace and uses this to instantiate a NamespaceExample object,
which is defined in this namespace. Notice the use of the namespace alias qualifier ( :: ). This forces the
search to start with the Introduction namespace alias. If a class called Introduction had been
introduced in the same scope, a conflict would happen. The :: operator allows the alias to be referenced
even if the conflict exists. The NamespaceExample class has one method, GetNamespace() , which uses
the GetType() method exposed by every class to access a Type object representing the class  s type. You
use this object to return a name of the class  s namespace:
*/

using System;
using Introduction = Wrox.ProCSharp.Basics;

namespace Wrox.ProCSharp.Basics
{
   class NameSpaceExample
   {
      public String GetNamespace()
      {
         return this.GetType().Namespace;
      }
   }
}


class Test
{
   /*
   Although it is common to specify the public modifier explicitly, because by definition the method must
   be called from outside the program, it doesn  t actually matter what accessibility level you assign to the
   entry - point method  it will run even if you mark the method as private .
   */

   private static void Main(String[] args)
   {
      Introduction::NameSpaceExample obj = new Introduction::NameSpaceExample();
      Console.WriteLine(obj.GetNamespace());
      return;
   }
}


