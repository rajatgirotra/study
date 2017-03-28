/*
 * Please read TupleTest.java first
 * Create a tool using Sets to add find the union, intersection, difference and complement of objects
 * of any type.
 */
import java.util.*;

public class Sets {
	public static <T> Set<T> union(Set<T> a, Set<T> b) {
		Set<T> un = new LinkedHashSet<T> (a);
		un.addAll(b);
		return un;
	}
	public static <T> Set<T> intersection(Set<T> a, Set<T> b) {
		Set<T> in = new LinkedHashSet<T> (a);
		in.retainAll(b);
		return in;	
	}
	public static <T> Set<T> difference(Set<T> a, Set<T> b) {
		Set<T> diff = new LinkedHashSet<T> (a);
		diff.removeAll(b);
		return diff;
	}
	
	//Everything not in the intersection
	public static <T> Set<T> complement(Set<T> a, Set<T> b) {
		return difference(union(a, b), intersection(a, b));
	}
}

/*
 * To show this in action we use EnumSet or Watercolors. 
 * So refer to Watercolors.java also
 * Please read WatercolorSets.java next
 */
