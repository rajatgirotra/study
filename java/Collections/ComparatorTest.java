/*
 * Please read Reverse.java first
 * As a second example, the following Comparator compares CompType objects based on their j values rather
 * than their i values
 */

import com.rajatgirotra.util.*;

import java.util.*;

class CompTypeComparator implements Comparator {
	public int compare(Object o1, Object o2) {
		int o1j = ((CompType)o1).j;
		int o2j = ((CompType)o2).j;
		return (o1j < o2j ? 1 : (o1j == o2j ? 0 : -1));
	}
}
public class ComparatorTest {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		CompType[] c = new CompType[10];
		Arrays2.fill(c, CompType.generator());
		
		System.out.println("before sorting: c = " + Arrays.toString(c));
		Arrays.sort(c);
		System.out.println("after sorting on i: c = " + Arrays.toString(c));
		Arrays.sort(c, new CompTypeComparator());
		System.out.println("after reverse sorting on j: c = " + Arrays.toString(c));
	}	
}

/*
The compare( ) method must return a negative integer, zero, or a
positive integer if the first argument is less than, equal to, or greater than
the second, respectively

Please read AlphabeticComparator.java next
*/