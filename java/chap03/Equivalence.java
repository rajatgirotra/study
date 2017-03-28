import java.util.*;

class Equivalence
{
   public static void main(String[] args)
   {
      Integer i1 = new Integer(47);
      Integer i2 = new Integer(47);
      Integer i3 = new Integer(-47);

      System.out.println("i1 == i2 is: " + (i1 == i2));
      System.out.println("i1 != i2 is: " + (i1 != i2));
      System.out.println("i1.equals(i2) is: " + i1.equals(i2));
      System.out.println("i1.equals(i3) is: " + i1.equals(i3));

      return;
   }
}

