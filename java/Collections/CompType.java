/*
 * In java, there is an interface java.lang.Comparable. This interface provides a single method.
 * compareTo(). The compareTo() method takes an object and returns -1, 0 or 1 if the object on which 
 * it is called is less than, equal to or greater than the object parameter passed.
 * 
 * The order of objects produced by using the Comparable interface is called a class' natural ordering & 
 * class' compareTo() method is called the natural comparison method.
 * Classes that implement Comparable interface can be sorted automatically by Arrays.sort() function or by
 * Collections.sort() function. They can also be used as keys in a sorted map or as elements in a sorted set.
 * without needing to use a comparator.
 * 
 * It is strictly recommended that this natural ordering of a class be consistent with equals that is:
 * e1.compareTo(e2) == 0 has the same boolean value as e1.equals(e2) except for e1.compareTo(null) which
 * throws a NullPointerException and e1.equals(null) which returns false.
 * We can then use Arrays.sort() function as shown below.
 */

import com.rajatgirotra.util.*;
import java.util.*;
public class CompType implements Comparable {
	int i;
	int j;
	public CompType(int i, int j) {
		this.i = i;
		this.j = j;
	}

	public String toString() {
		return "[i = " + i + ", j = " + j + "]";
	}

	private static Random rand = new Random();
	private static int ranInt() {
		return rand.nextInt(100);
	}

	public static Generator generator() {
		return new Generator() {
			public Object next() {
				return new CompType(ranInt(), ranInt());
			}
		};
	}
	
	public int compareTo(Object rv) {
		int rvi = ((CompType)rv).i;
		return ( i < rvi ? -1 : (i == rvi ? 0 : 1));
	}
    
	public static void main(String[] args) {
		CompType[] a = new CompType[10];
		Arrays2.fill(a, generator());
		System.err.println(
				"before sorting, a = " + Arrays.asList(a));
		Arrays.sort(a);
		System.err.println(
				"after sorting, a = " + Arrays.asList(a));
	}
}

/*
 * public static void sort(Object[] a)Sorts the specified array of objects into ascending order,
 * according to the natural ordering of its elements. All elements in the array must implement
 * the Comparable interface. Furthermore, all elements in the array must be mutually comparable
 * (that is, e1.compareTo(e2) must not throw a ClassCastException for any elements e1 and e2 in
 * the array).
 * 
 * If Comparable hadn’t been implemented, then you’d get a compile-time error message when you
 * tried to call sort( ).
 * 
 * Please see StringSorting.java first
 */

