/*
 * Please read CollectionSequence.java first
 * The foreach JAVA syntax works with Arrays as well as Collection. Infact it will work with any class that implements
 * the Iterable interface. This interface has a iterator() function which must be implemented. Since Collection interface
 * also extends from Iterable, we can use the foreach syntax with Collection.
 * 
 * The program below implememts Iterable.
 * you might think that since arrays can be used with foreach syntax they are also derived from Iterable,
 * so please note that this is not the case.
 * Although arrays can be used with JAVA foreach syntax, yet they are not Iterable. See ArraysIsNotIterable.java for more.
 */

import java.util.*;
public class IterableClass implements Iterable<String> {
	protected String[] words = ("And this is how we know the earth to be banana-shaped").split(" ");

	public Iterator<String> iterator() {
		return new Iterator<String>() {
			private int index = 0;
			public boolean hasNext() {
				return index < words.length;
			}
			public void remove() {
				throw new UnsupportedOperationException();
			}
			public String next() {
				return words[index++];
			}
		};
	}

	public static void main(String[] args) {
		//The foreach syntax below basically calls the iterator() function on the object passed after the ":"
		//in this case it calls the iterator() function on the object of type IterableClass.
		for(String s : new IterableClass()) {
			System.out.print(s + ": ");
		}
	}
}

/*
Please read ArrayIsNotIterable.java next
*/