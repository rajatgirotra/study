/*
 * Please read ArrayIsNotIterable.java first.
 * Demonstrate how to use the foreach syntax in JAVA.
 */

import java.util.*;
class ReverseArrayList<T> extends ArrayList<T> {
	
	//c'tor
	public ReverseArrayList(Collection<T> c) {
		super(c);
	}
	
	public Iterable<T> reversed() {
		return new Iterable<T>() {			
			public Iterator<T> iterator() {
				return new Iterator<T>() {
					int current = size() - 1;
					public boolean hasNext() {
						return (current > -1);
					}
					public T next() {
						return get(current--);
					}
					public void remove() {
						throw new UnsupportedOperationException();
					}
				};
			}
		};
	}
}
public class AdapterMethodIdiom {
	public static void main(String[] args) {
		ReverseArrayList<String> ral = new ReverseArrayList<String>(Arrays.asList("To be or not to be".split(" ")));
		
		for(String s : ral) {
			System.out.print(s + " ");			
		}
		System.out.println();
		for(String s1 : ral.reversed()) {
			System.out.print(s1 + " ");
		}	
	}
}
