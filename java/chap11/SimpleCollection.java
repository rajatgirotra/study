/*
 * Please read Must_Read_2.txt first.
 */

import java.util.*;
public class SimpleCollection {
	public static void main(String[] args) {
		Collection<Integer> ci = new HashSet<Integer>();
		for(int i = 0; i < 10; ++i) {
			ci.add(i);
		}
		for(int i = 0; i < 10; ++i) {
			ci.add(i);
		}
		for(Integer c : ci) {
			System.out.print(c);
		}		
	}
}
/*
 * Please read AddingGroups.java next
 */
