/*
Please read 1.cs first.

Here we show that C# compiler automatically deduces the type of the variable you declare based on the right hand side
We then print it out using the System.Type class
*/

using System;

namespace Wrox.ProCSharp.Basics
{
   class TypeTest { }
   
   class Program
   {
      static void Main(string[] args)
      {
         var name = "Bugs Bunny";
         var age = 25;
         var isMature = false;
         var typeTestObj = new TypeTest();         
         int i = 32;

         Type nameType = name.GetType();
         Type ageType = age.GetType(); 
         Type matureType = isMature.GetType();
         Type typeTestObjType = typeTestObj.GetType();
         Type iType = i.GetType();

         Console.WriteLine("name is of type " + nameType.ToString());
         Console.WriteLine("age is of type " + ageType.ToString());
         Console.WriteLine("isMature is of type " + matureType.ToString());
         Console.WriteLine("typeTestObj is of type " + typeTestObjType.ToString());
         Console.WriteLine("i is of type " + iType.ToString());
         Console.WriteLine(iType);

         return;
      }
   }
}

