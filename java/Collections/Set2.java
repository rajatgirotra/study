/* Please read Set1.java first
 * When creating your own types, be aware that a Set needs a way to
 * maintain a storage order, which means you must implement the
 * Comparable interface and define the compareTo( ) method. Here’s an
 * example.
 */

import java.util.*;

@SuppressWarnings("unchecked")
class MyType implements Comparable {
	public int compareTo(Object obj) {
		MyType m = (MyType)obj;
		//return name.compareTo(m.name);
		return (rollno < m.rollno ? -1 : ((rollno == m.rollno) ? 0 : 1));
	}
	private int rollno;
	private String name;
	
	public MyType(int rollno, String s) {
		this.rollno = rollno;
		this.name = s;
	}
	
	public String toString() {
		return Integer.toString(rollno);
	}
}

@SuppressWarnings("unchecked")
public class Set2 {
	
	private static Random rand = new Random();
	private static void fill(Set s, int size) {
		for(int i = 0 ; i < size; ++i) {
			int no = rand.nextInt(100);
			s.add(new MyType(no, "ABC"));
			System.out.println("Inserting number#: " + no);
		}			
	}
	
	public static void main(String[] args) {
		Set hs = new HashSet();
		fill(hs, 5);
		System.out.println(hs);
		
		SortedSet ts = new TreeSet();
		fill(ts, 5);
		System.out.println(ts);
		System.out.println(ts.headSet((Object)(new MyType(58, "ABC"))));
		
		Set lhs = new LinkedHashSet();
		fill(lhs, 5);
		System.out.println(lhs);
	}
}

/*
Please read Map1.java next
*/