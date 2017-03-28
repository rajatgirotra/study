/*
 * Please read PetMap.java first
 * Demonstrate a MultiMap kind of functionality
 */

import com.rajatgirotra.*;
import static com.rajatgirotra.util.Print.*;
import java.util.*;
import typeinfo.pets.*;
public class MapOfList {
	private static Map<Person, List<? extends Pet>> petPeople = new HashMap<Person, List<? extends Pet>>();
	static {
			petPeople.put(new Person("Dawn"),    Arrays.asList(new Cymric("Molly"),new Mutt("Spot")));
			petPeople.put(new Person("Kate"),    Arrays.asList(new Cat("Shackleton"), new Cat("Elsie May"), new Dog("Margrett")));
			petPeople.put(new Person("Marilyn"), Arrays.asList(new Pug("Louie aka Louis Snorkelstein Dupree"), new Cat("Stanford aka Stinky el Negro"), new Cat("Pinkola")));
			petPeople.put(new Person("Luke"),    Arrays.asList(new Rat("Fuzzy"), new Rat("Fizzy")));
			petPeople.put(new Person("Isaac"),   Arrays.asList(new Rat("Freckly")));
	}	
	public static void main(String[] args) {
		//Print the keys and values individually first 
		//keySet() returns a set View of the keys of the map
		//values() returns a Collection of the values in the map
		System.out.println("People: " + petPeople.keySet());
		System.out.println("Pets: " + petPeople.values());
		
		//now print them together
		for(Person p : petPeople.keySet()) {
			System.out.println(p + " has:");
			for(Pet pet : petPeople.get(p)) {
				System.out.println("     " + pet);
			}
		}
	}
}

/*
Please read QueueDemo.java next
*/