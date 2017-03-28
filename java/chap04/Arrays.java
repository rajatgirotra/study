import java.util.*;

class Arrays
{

   public static void main(String[] args)
   {
      int[] a1 = { 1, 2, 3, 4, 5 };
      int[] a2;

      a2 = a1;
      for(int i = 0; i < a2.length; ++i)
         ++a2[i];

      for(int i = 0; i < a1.length; ++i)
         System.out.println("a1["+i+"]  = " + a1[i]);
   }
}
 
