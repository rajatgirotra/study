//using static c'tors

using System;
using System.Drawing;

namespace Wrox.ProCSharp.chap03
{
   class StaticCtorExample
   {
      public static readonly Color BackColor;

      static StaticCtorExample()
      {
         DateTime now = DateTime.Now;
         if(now.DayOfWeek == DayOfWeek.Saturday || now.DayOfWeek == DayOfWeek.Sunday)
            BackColor = Color.Green;
         else
            BackColor = Color.Red;
      }

      public StaticCtorExample()
      {
      }

      public static void Main(String[] args)
      {
         Console.WriteLine("Back Color is: " + StaticCtorExample.BackColor.ToString());
         return;
      }
   }
}

