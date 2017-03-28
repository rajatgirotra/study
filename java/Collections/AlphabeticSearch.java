/*
 * Please read AlphabeticSorting.java first
 * If you have sorted an object array using a Comparator (primitive arrays do not allow sorting
 * with a Comparator), you must include that same Comparator when you perform a binarySearch( )
 * (using the overloaded version of the method that’s provided). For example, the
 * AlphabeticSorting.java program can be modified to perform a search:
 */

import com.rajatgirotra.util.*;
import java.util.*;

public class AlphabeticSearch {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		String[] str = new String[10];
		Arrays2.RandStringGenerator randString = new Arrays2.RandStringGenerator(8);
		Arrays2.fill(str, randString);
		Arrays.sort(str, new AlphabeticComparator());
		System.out.println("String array: " + Arrays.toString(str));
		System.out.println("Item: " + str[5]);
		
		int index = Arrays.binarySearch(str, str[5], new AlphabeticComparator());
		System.out.println("Index: " + index);
	}
}

/*
 * Whenever using Arrays.binarySearch() with a Comparator; make sure that the list has also
 * been sorted using the same comparator.
 * 
 * Please read InfiniteRecursion.java next
 */
