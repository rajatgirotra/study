/*
 * Please read GenericVarargs.java first
 */

import generics.coffee.Coffee;
import generics.coffee.CoffeeGenerator;
import generics.coffee.Generator;

import java.util.ArrayList;
import java.util.Collection;

public class Generators {
	public static <T> Collection<T> makeList(Collection<T> coll, Generator<T> gen, int n) {
		for(int i = 0; i < n; ++i) {
			coll.add(gen.next());
		}
		return coll;
	}

	public static void main(String[] args) {
		Collection<Coffee> cf = makeList(new ArrayList<Coffee>(), new CoffeeGenerator(), 10);
		for(Coffee c : cf) {
			System.out.println(c);
		}
		/*
		Collection<Integer> fnumbers = fill(
				new ArrayList<Integer>(), new Fibonacci(), 12);
		for(int i : fnumbers)
			System.out.print(i + ", ");
		*/
	}
}

/*
Please read BasicGenerators.java next
*/