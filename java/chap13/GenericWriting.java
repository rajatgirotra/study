/*
 * Please read SuperTypeWildcards.java first
 */

import java.util.*;  

class Unrelated {
	
}
public class GenericWriting {
	static <T> void writeExact(List<T> list, T item) {
		list.add(item);
	}
	
	static List<Apple> apples = new ArrayList<Apple>();
	static List<Fruit> fruits = new ArrayList<Fruit>();
	static List<Unrelated> unrelated = new ArrayList<Unrelated>();
	
	static void f1() {
		writeExact(apples, new Apple()); //this is ok;
		writeExact(fruits, new Fruit()); // this is ok too
		writeExact(apples, new Jonathan());
		writeExact(fruits, new Jonathan());
		//writeExact(apples, new Fruit()); //NOT OK. 
		//YOU CANT ASSIGN A GENERIC INVOLVING APPLES TO A GENERIC INVOLVING FRUITS
		//A list of apples is not a list of fruits. A list of apples will only contain apples or any subtypes of apples.
	}
	
	static <T> void writeWithWildcard(List<? super T> list, T item) {		
		list.add(item);
	}	
	
	static void f2() {
		writeWithWildcard(apples, new Apple());
		writeWithWildcard(fruits, new Apple());
		writeWithWildcard(apples, new Fruit());
		
		List<? super Apple> app = fruits;
		//writeWithWildcard(unrelated, new Apple());
	}
	
	public static void main(String[] args) {
		f1();
		f2();
	}
}

/*
Please read WildCards.java next
*/