/*
 * Please read ComparatorTest.java first.
 * You may also want to group the words together regardless of case, and you can do this by
 * defining a Comparator class, thereby overriding the default String Comparable behavior.
 * For reuse, this will be added to the util package:
 */

package com.rajatgirotra.util;

import java.util.*;
public class AlphabeticComparator implements Comparator{
	public int compare(Object o1, Object o2) {
		String s1 = (String)o1;
		String s2 = (String)o2;
		return s1.toLowerCase().compareTo(s2.toLowerCase());
	}
}

/*
Please read AlphabeticSorting.java next
*/