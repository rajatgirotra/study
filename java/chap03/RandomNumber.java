import java.util.*;

class RandomNumber
{
   public static void main(String[] args)
   {
     Random rand = new Random();
     int i = 0, j = 0, k = 0;

     j = rand.nextInt(100);
     k = rand.nextInt(100);

     System.out.println("j = " + j);
     System.out.println("k = " + k);
     System.out.println("j + k = " + (j+k));

     return;
   }
}

