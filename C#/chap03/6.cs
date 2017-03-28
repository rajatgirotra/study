// Using C# properties
using System;

namespace Wrox.ProCSharp.chap03
{
   class MainEntryPoint
   {
      private string myName;
     
      public string MyName
      {
         get
         {
            return myName;
         }

         set
         {
             myName = value;
         }
      }

      public string MyCompany { get; set; }

      public static void Main(String[] args)
      {
         MainEntryPoint obj = new MainEntryPoint();
         obj.MyName = "Rajat";
         Console.WriteLine(obj.MyName);

         obj.MyCompany = "ION Trading";
         Console.WriteLine(obj.MyCompany);

         return;
      }
   }
}

       
