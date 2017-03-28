/* Read Must_Read_2.txt first & then understand this simple program */
import java.util.*;
public class SimpleCollection {
	public static void main(String[] args) {
		Collection c = new ArrayList();
		for(int i = 0; i < 10; ++i) {
			c.add(Integer.toString(i));
		}
		
		c.add(3.456); // Collections are heterogenous.
		Iterator iter = c.iterator();
		while(iter.hasNext()) {
			System.out.println(iter.next());
		}
	}
}

/*
Also note that these collections are heterogenous, i.e. you can add anything to a Collection. It 
needn't necessarily be the same type.

Next note that ArrayList() is used for random element access.
It is slow for insertions & deletions in the middle of the List.
You should use LinkedList() for that. LinkedList() provide fast insertions & deletions anywhere in the 
list but it is slow for Random Access.
Moreover, LinkedList() also provide functions like getFirst(), addFirst(), getLast(), setLast() using 
which you can implement a List as a Stack or a Queue.

Please read SimpleUtilityFunctions.java next
*/