import java.util.*;

class Cast
{
   public static void main(String[] args)
   {
      float f4 = 1e-7F; // 10 to the power
      System.out.println(f4);
      return;
   }
}




/*
the compiler normally takes exponential numbers as doubles, so without
the trailing f it will give you an error telling you that you must use a cast
to convert double to float.
*/
