/*
 * Please read AlphabeticComparator.java first
 *  After going through this program, you should understand this:
 * That Arrays.sort() or Collections.sort() sorts a list in the natural ordering i.e. using the 
 * compareTo(Object) function of the Comparable interface. If you want to override that, then you can
 * define your own new class that implements Comparator and define the compare(Object, Object) and 
 * equals() function, then use Arrays.sort(list, Comparator) to sort using your new comparator.
 */

import com.rajatgirotra.util.*;
import java.util.*;

public class AlphabeticSorting {
	public static void main(String[] args) {
		String[] str = new String[10];
		Arrays2.fill(str, new Arrays2.RandStringGenerator(10));
		System.out.println("before sort str: " + Arrays.asList(str));
		Arrays.sort(str, new AlphabeticComparator());
		//Arrays.sort(str);
		System.out.println("after sort str: " + Arrays.asList(str));
	}	
}

/*
Please read AlphabeticSearch.java next
*/