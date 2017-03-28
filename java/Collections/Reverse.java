/*
 * Please read StringSorting.java first.
 * 
 * Now suppose someone hands you a class that doesn’t implement Comparable, or they hand you this class
 * that does implement Comparable, but you decide you don’t like the way it works and would
 * rather have a different comparison method for the type. The solution is in contrast to hard-wiring
 * the comparison code into each different object. Instead, the strategy design pattern4 is used.
 * With a strategy, the part of the code that varies is encapsulated inside its own class (the strategy
 * object). You hand a strategy object to the code that’s always the same, which uses the strategy to
 * fulfill its algorithm. That way you can make different objects to express different ways of 
 * comparison and feed them to the same sorting code. Here, you create a strategy by defining a
 * separate class that implements an interface called Comparator. This has two methods,
 * compare( ) and equals( ). However, you don’t have to implement equals( ) except for special
 * performance needs, because anytime you create a class it is implicitly inherited from Object,
 * which has an equals( ). So you can just use the default Object equals( ) and satisfy the contract
 * imposed by the interface. 
 * 
 * 
 * The Collections class (which we’ll look at more later) contains a single
 * Comparator that reverses the natural sorting order. This can easily be
 * applied to the CompType:
 */
import com.rajatgirotra.util.*;
import java.util.*;

public class Reverse {
	public static void main(String[] args) {
		CompType[] a = new CompType[10];
		Arrays2.fill(a, CompType.generator());
		System.out.println(
				"before sorting, a = " + Arrays.asList(a));
		Arrays.sort(a, Collections.reverseOrder());
		System.out.println(
				"after sorting, a = " + Arrays.asList(a));
	}
}

/*
 * Please read ComparatorTest.java next
 */
