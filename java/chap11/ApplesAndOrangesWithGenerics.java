/*
 * Please read ApplesAndOrangesWithoutGenerics.java first.
 * Please uncomment line marked A.
 */

import java.util.*;

class Apples {
	private static long counter = 0;
	private long id = counter++;
	public long id() {
		return id;
	}
}

class Oranges { 
}
public class ApplesAndOrangesWithGenerics {
	public static void main(String[] args) {
		List<Apples> list = new ArrayList<Apples>();
		
		for(int i = 0; i < 5; ++i)
			list.add(new Apples());
		
		//list.add(new Oranges());    // ----->>>> A
		
		for (int i = 0; i < list.size(); ++i)
			System.out.println(list.get(i).id());
		
		//Using for each
		//d, r, c, djewlk, you can use anything.
		for(Apples dhkjewhdkewq : list) {
			System.out.println(dhkjewhdkewq.id());
		}
	}
}

/*
 * Compile time error: The method add(Apples) in the type ArrayList<Apples> is not applicable for the arguments (Oranges)
 * Since the List knows what type it holds, it does the cast for you when you call get( ). Thus, with generics you not only
 * know that the compiler will check the type of object that you put into a container, but you also get cleaner syntax when
 * using the objects in the container. The example also shows that, if you do not need to use the index of each element, you
 * can use the foreach syntax to select each element in the List. You are not limited to putting the exact type of object into
 * a container when you specify that type as a generic parameter. Upcasting works the same with generics as it does with other types:
 * 
 *  Please read GenericsAndUpcasting.java next
 */