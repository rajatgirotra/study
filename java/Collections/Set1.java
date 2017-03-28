/* Please read MouseList.java first
 * Understanding Set functionality
 * Each element that you add to a Set must be unique. Object uniqueness is established
 * using the Objects equals() method.
 * 
 *  HashSet - Used for faster lookups
 *  TreeSet - Used to maintain a particular order
 *  LinkedHashSet - Look up performance is same as HashSet, but insertion order is maintained.
 *
 * 
 */


import java.util.*;

@SuppressWarnings("unchecked")
public class Set1 {
	static void fill(Set s) {
		s.addAll(Arrays.asList("one two three four five six seven".split(" ")));
	}
	public static void test(Set s) {
		//Strip qualifiers from class name:
		System.out.println(
				s.getClass().getName().replaceAll("\\w+\\.", ""));
		System.out.println(
				s.getClass().getName()); // this is to see what replaceAll() above is doing.
		
		fill(s); fill(s); fill(s);
		System.out.println(s); // No duplicates!
		//Add another set to this one:
		s.addAll(s);
		s.add("one");
		s.add("one");
		s.add("one");
		System.out.println(s);
		//Look something up:
		System.out.println("s.contains(\"one\"): " +
				s.contains("one"));
		
		//Printer.printAll(s.iterator());
	}
	public static void main(String[] args) {
		test(new HashSet()); // any ordering; never ever rely on ordering in a Hashed set
		test(new TreeSet()); //Ordered set: in this case alphabetically. Is it the natural ordering?
		test(new LinkedHashSet()); // Insertion order is maintained here.
	}
}

/*
Please read Set2.java next
*/