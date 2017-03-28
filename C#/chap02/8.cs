//Using C3 enumerations

using System;

namespace Wrox.ProCSharp.Basics
{
   class MainEntryPoint
   {
      public enum TimeOfDay
      {
         Morning   = 0x01,
         Afternoon = 0x02,
         Evening   = 0x03
      }

      public static void WriteGreeting(TimeOfDay timeofDay)
      {
         switch(timeofDay)
         {
            case TimeOfDay.Morning:   Console.WriteLine("Good " + timeofDay.ToString());
                                      break;
  
            case TimeOfDay.Afternoon:   Console.WriteLine("Good " + timeofDay.ToString());
                                      break;
 
            case TimeOfDay.Evening:   Console.WriteLine("Good " + timeofDay.ToString());
                                      break;

            default:  Console.WriteLine("What time is it any way..!!??");
                      break;
         }
      }

      public static void Main(String[] args)
      {
         WriteGreeting(TimeOfDay.Morning);
         /* To get the integer for an enum use the Enum.Parse() method */
         TimeOfDay time2 = (TimeOfDay)Enum.Parse(typeof(TimeOfDay), "eVeNiNg", true);
         WriteGreeting(time2);
         return;
      }
   }
}

