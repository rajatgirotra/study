/* 
 * Please read ComparingArrays.java first.
 * Performing a binary search using Arrays class. 
 * make sure the input array is sorted else results are unpredictable
 */
 
import java.util.*;
import com.rajatgirotra.util.*;

public class ArraySearching {
	public static void main(String[] args) {
		int[] a = new int[5];
		Arrays2.RandIntGenerator randInt = new Arrays2.RandIntGenerator(20);
		Arrays2.fill(a, randInt);
		Arrays.sort(a);
		
		int item = randInt.next();
		System.out.println("Array: " + Arrays.toString(a));
		System.out.println("Item: " + item);
		System.out.println(Arrays.binarySearch(a, item));
	}
}

/*
 * Returns:
 * index of the search key, if it is contained in the list; otherwise, (-(insertion point) - 1).
 * The insertion point is defined as the point at which the key would be inserted into 
 * the list: the index of the first element greater than the key, or list.size(), if all 
 * elements in the list are less than the specified key. 
 * 
 * Note that this guarantees that the return value will be >= 0 if and only if the key is found.
 * 
 * i.e. the insertion point is the index at which the item should be inserted.
 * 
 * If the array contains duplicate elements, there is no guarantee which one
 * will be found. The algorithm is thus not really designed to support duplicate elements, 
 * but rather to tolerate them. If you need a sorted list of nonduplicated elements, use a 
 * TreeSet (to maintain sorted order) or LinkedHashSet
 * 
 * Please read CompType.java next.
 */
