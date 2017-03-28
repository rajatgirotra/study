/*
The Class.isInstance method provides a way to dynamically call the
instanceof operator. Thus, all those tedious instanceof statements can
be removed in the PetCount example:

public boolean isInstance(Object obj)

Determines if the specified Object is assignment-compatible with the object represented by
this Class. This method is the dynamic equivalent of the Java language instanceof operator.
The method returns true if the specified Object argument is non-null and can be cast to the
reference type represented by this Class object without raising a ClassCastException.
It returns false otherwise.
*/

//: c10:PetCount3.java
// Using isInstance()
import java.util.*;
public class PetCount3 {
	private static Random rand = new Random();
	public static void main(String[] args) {
		Object[] pets = new Object[15];
		Class[] petTypes = {
				// Class literals:
				Pet.class,
				Dog.class,
				Pug.class,
				Cat.class,
				Rodent.class,
				Gerbil.class,
				Hamster.class,
		};
		try {
			for(int i = 0; i < pets.length; i++) {
				// Offset by one to eliminate Pet.class:
				int rnd = 1 + rand.nextInt(petTypes.length - 1);
				pets[i] = petTypes[rnd].newInstance();
			}
		} catch(InstantiationException e) {
			System.out.println("Cannot instantiate");
			System.exit(1);
		} catch(IllegalAccessException e) {
			System.out.println("Cannot access");
			System.exit(1);
		}
		AssociativeArray map =
			new AssociativeArray(petTypes.length);
		for(int i = 0; i < petTypes.length; i++)
			map.put(petTypes[i].toString(), new Counter());
		for(int i = 0; i < pets.length; i++) {
			Object o = pets[i];
			// Using Class.isInstance() to eliminate
			// individual instanceof expressions:
			for(int j = 0; j < petTypes.length; ++j)
				if(petTypes[j].isInstance(o)) //whether(petTypes[j](o)) will throw a ClassCastException or not
					((Counter)map.get(petTypes[j].toString())).i++;
		}
		// List each individual pet:
		for(int i = 0; i < pets.length; i++)
			System.out.println(pets[i].getClass());
		// Show the counts:
		System.out.println(map);
	}
}