import java.util.*;

class ArrayClassObj {

   static Random rand = new Random();
   public static void main(String[] args) {
      Integer[] a = new Integer[rand.nextInt(20)];

      for(int i = 0; i < a.length; ++i) {
         a[i] = new Integer(rand.nextInt(500)); // Create an Integer with value between 0 & 500
         System.out.println("a[" + i + "]  =  " + a[i]);
      }
   }
}
