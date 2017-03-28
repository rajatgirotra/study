/*
 * Please read FillingArrays.java first.
 * Using Collections.fill() to populate an ArrayList
 * Aslo comment/uncomment the for loop and see the output.
 */

import java.util.*;

@SuppressWarnings("unchecked")
public class FillingLists {
	public static void main(String[] args) {
		List list = new ArrayList();
		System.out.println(list.size());
	
		for(int i = 0; i < 10; ++i) {
			list.add("");			
		}
	
		System.out.println(list);
		Collections.fill(list, "Hello");
		System.out.println(list);
	}
}

/*
This method is made even less useful by the fact that it can only replace
elements that are already in the List, and will not add new elements.

Please read FillTest.java next
*/