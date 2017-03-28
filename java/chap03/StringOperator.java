import java.util.*;

class StringOperator
{
   public static void main(String[] args)
   {
      String s = "asdf";
      int x = 0, y = 9, z = -1;
      System.out.println(s + x + y + z); // Java compiler concatenates the integer variables as a string instead of adding them together
      System.out.println(x + s);
      return;
   }
}

