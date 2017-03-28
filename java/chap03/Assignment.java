import java.util.*;

class NNumber
{
   int i;
}

public class Assignment
{
   public static void main(String[] args)
   {
      NNumber n1 = new NNumber();
      NNumber n2 = new NNumber();

      n1.i = 9;
      n2.i = 47;

      System.out.println("1. n1.i: " + n1.i + "    n2.i: " + n2.i);

      n1 = n2; 
      
      System.out.println("2. n1.i: " + n1.i + "    n2.i: " + n2.i);

      n2.i = 27;

      System.out.println("3. n1.i: " + n1.i + "    n2.i: " + n2.i);

      return;
   }
}
