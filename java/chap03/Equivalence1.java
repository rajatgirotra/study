import java.util.*;

class Number
{
   int i;
}

class Equivalence1
{
   public static void main(String[] args)
   {
      Number n1 = new Number();
      Number n2 = new Number();
      Number n3 = new Number();

      n1.i = n2.i = n3.i = 100;

      System.out.println("n1 == n2 is: " + (n1 == n2));
      System.out.println("n1 == n3 is: " + (n1 == n3));
      System.out.println("n1.equals(n2) is: " + n1.equals(n2));
      System.out.println("n2.equals(n3) is: " + n2.equals(n3));

      return;
   }
}

/*
This is because the default
behavior of equals( ) is to compare references. So unless you override
equals( ) in your new class you wont get the desired behavior.
Unfortunately, you wont learn about overriding until Chapter 7, but being
aware of the way equals( ) behaves might save you some grief in the
meantime.
*/
