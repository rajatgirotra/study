import java.util.*;

class ArrayNew
{
   static Random rand = new Random();

   public static void main(String[] args)
   {
      int[] a1 = new int[rand.nextInt(20)];

      System.out.println("length of a1 = " + a1.length);
 
      for(int i = 0; i < a1.length; ++i)
         System.out.println("a1["+i+"]  = " + a1[i]);
   }
}

/*

What if you dont know how many elements youre going to need in your
array while youre writing the program? You simply use new to create the
elements in the array. Here, new works even though its creating an array
of primitives (new wont create a nonarray primitive):

The size of the array is chosen at random, using the Random.nextInt( )
method, which produces a value from zero to that of its argument.
Because of the randomness, its clear that array creation is actually
happening at run time. In addition, the output of this program shows that
array elements of primitive types are automatically initialized to empty
values. (For numerics and char, this is zero, and for boolean, its false.)

Even if the array is of user defined type, for example: some class say Book, 
then the array will be initialized with all null.

*/
