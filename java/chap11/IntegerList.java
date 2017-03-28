/*
 * Please read ListIteration.java first
 * Take elements from one List<Integer> & add them to a second List<Integer> in reverse order
 */
import java.util.*;

public class IntegerList {
	public static void main(String[] args) {
		Integer[] intArray = new Integer[] {1,2,3,4,5,6,7,8,9};
		List<Integer> intList = new ArrayList<Integer>(Arrays.asList(intArray));
		List<Integer> copyList = new ArrayList<Integer>();
		ListIterator<Integer> copyListIter = copyList.listIterator();
		System.out.println("Original list: " + intList);
		for(Integer c : intList) {
			copyListIter.add(c);
			copyListIter.previous();
		}
		System.out.println("Copy list: " + copyList);
	}
}

/*
 * Please read Stack.java first
 */
