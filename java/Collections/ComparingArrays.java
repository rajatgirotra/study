/* 
Please read CopyingArrays.java first
Comparing arrays
using Arrays.equals(a, b)

Arrays provides the overloaded method equals( ) to compare entire
arrays for equality. Again, these are overloaded for all the primitives, and
for Object. To be equal, the arrays must have the same number of
elements and each element must be equivalent to each corresponding
element in the other array, using the equals( ) for each element. (For
primitives, that primitive’s wrapper class equals( ) is used; for example,
Integer.equals( ) for int.
 */

import java.util.*;

public class ComparingArrays {
	public static void main(String[] args) {
		int[] i = new int[10];
		int[] j = new int[10];
		Arrays.fill(i, 34);
		Arrays.fill(j, 34);
		System.out.println(Arrays.equals(i, j));
		i[3] = 23;
		System.out.println(Arrays.equals(i, j));
		System.out.println(Arrays.toString(i));
		
		String[] src = new String[5];
		Arrays.fill(src, "Hi");
		
		String[] s = new String[] { "Hi", "Hi", "Hi", "Hi", "Hi" };
		System.out.println(Arrays.equals(src, s));
		src[2] = "Bye";
		System.out.println(Arrays.equals(src, s));
		System.out.println(Arrays.toString(src));
	}
}

/*
Please read ArraySearching.java next
*/