/* Please read Printer.java first
 * Collection: a group of individual elements, often with some rule applied to them. 
 * A List must hold the elements in a particular sequence, and a Set cannot have any
 * duplicate elements. (A bag, which is not implemented in the Java container library—since
 * Lists provide you with enough of that functionality—has no such rules.)
 * 
 * Map: a group of key-value object pairs. At first glance, this might seem like it ought
 * to be a Collection of pairs, but when you try to implement it that way the design gets 
 * awkward, so it’s clearer to make it a separate concept. On the other hand, it’s convenient 
 * to look at portions of a Map by creating a Collection to represent that portion. Thus, a 
 * Map can return a Set of its keys, a Collection of its values, or a Set of its pairs. 
 * Maps, like arrays, can easily be expanded to multiple dimensions without adding new 
 * concepts: you simply make a Map whose values are Maps (and the values of those Maps 
 * can be Maps, etc.)
 * 
 * Collection is an interface at the top level. Then another interface List extends it. Then
 * you have a lot of subclasses implementing the List interface.
 * 
 * Collection
 * -- List
 * ---- ArrayList or Linked List etc etc. Look at JAVA documentation online for more.
 * 
 * interface Collection { }
 * interface List extends Collection { }
 * class ArrayList implements List { }
 * 
 * interface Collection { }
 * interface Set extends Collection { }
 * class HashSet implements Set { }
 * 
 * interface Map { }
 * class HashMap implements Map { }
 * 
 * The ArrayList is a type of List, and HashSet is a type of Set. 
 * To add items to any Collection, there’s an add( ) method.
 * 
 * To add elements to a Map there’s a put( ) method that takes a key and a value as arguments
 */

import java.util.*;

@SuppressWarnings("unchecked")
public class PrintingContainers {
	static Collection fill(Collection c) {
		c.add("Dog");
		c.add("Dog");
		c.add("Cat");
		return c;
	}
	static Map fill(Map m) {
		m.put("Dog", "Bruno");
		m.put("Dog", "Scooby Doo");		
		m.put("Cat", "Tom");	
		return m;		
	}
	
	public static void main(String[] args) {
		System.out.println(fill(new ArrayList()));
		System.out.println(fill(new HashSet()));
		System.out.println(fill(new HashMap()));

		System.out.println();
		System.out.println(fill(new LinkedHashSet()));
		System.out.println(fill(new LinkedHashMap()));

	}
}

/*
The Set, however, only accepts one of each object and it uses its own internal ordering method
(in general, you are only concerned with whether or not something is a member of the Set,
not the order in which it appears—for that you’d use a List). And the Map also only accepts one 
of each type of item, based on the key, and it also has its own internal ordering and does not
care about the order in which you enter the items. If maintaining the insertion sequence is
important, you can use a LinkedHashSet or LinkedHashMap.

Please read Mouse.java next
*/