/* Using instanceof,
 * Class.forName(),
 * Class.newInstance() etc etc.
 * Object.getClass()
 */

/* 
 * Class.forName(String id) will return a reference to the Class object for class whose name is "id" 
 * Class.newInstance() - will create a new object a class to which that Class object belongs.
 * Object.getClass() - Returns the Class object associated with the given object.
 * System.out.println(Class obj) - will print "class" or "interface", then space, then the name of the class.
 */
import java.util.*;

class Pet { }
class Dog extends Pet { }
class Pug extends Dog { }

class Cat extends Pet { }
class Rodent extends Pet { }
class Gerbil extends Rodent { }
class Hamster extends Rodent { }

class Counter {
	int i;
	public String toString() {
		return Integer.toString(i);
	}
}

class AssociativeArray {
	private Object[][] pairs;
	private int index;

	public AssociativeArray(int length) {
		pairs = new Object[length][2];
	}

	public Object get(String key) {
		for(int i = 0; i < pairs.length; ++i) {
			if(key.equals(pairs[i][0])) {
				return pairs[i][1];					
			}		
		}
		throw new RuntimeException("Failed to find key");
	}

	public void put(Object key, Object value) {
		if(index < pairs.length) {
			pairs[index++] = new Object[] { key, value };			
		}
		else
			throw new ArrayIndexOutOfBoundsException();
	}

	public String toString() {
		String result = "";
		for(int i = 0; i < index; ++i) {
			result += (pairs[i][0] + ":  " + pairs[i][1] + "\n");
		}
		return result;
	}
}
public class PetCount {
	static private String[] typenames = { "Dog", "Pet", "Pug", "Cat", "Rodent", "Gerbil", "Hamster" };
	static private Random rand = new Random();

	public static void main(String[] args) {
		Object[] pets = new Object[15];
		try {
			Class[] classNames =  { Class.forName("Dog"),
					Class.forName("Pet"),
					Class.forName("Pug"),
					Class.forName("Rodent"),
					Class.forName("Cat"),
					Class.forName("Gerbil"),
					Class.forName("Hamster") };

			for (int i = 0; i < pets.length; ++i) {
				pets[i] = classNames[rand.nextInt(classNames.length)].newInstance();
			}	
		}catch (ClassNotFoundException e) {
			System.out.println("Class not found..!!");
			System.exit(1);
		} catch (InstantiationException e) {
			System.out.println("Cannot instantiate");
			System.exit(1);	
		} catch (IllegalAccessException e) {
			//violation of the Java security mechanism
			System.out.println("Cannot access");
			System.exit(1);
		}

		AssociativeArray map = new AssociativeArray(typenames.length);
		for(int i = 0; i < typenames.length; ++i) {
			map.put(typenames[i], new Counter());
		}

		for(int i = 0; i < pets.length; ++i) {
			Object o = pets[i];
			if(o instanceof Pet)
				((Counter)map.get("Pet")).i++;
			if(o instanceof Dog)
				((Counter)map.get("Dog")).i++;
			if(o instanceof Pug)
				((Counter)map.get("Pug")).i++;
			if(o instanceof Cat)
				((Counter)map.get("Cat")).i++;
			if(o instanceof Rodent)
				((Counter)map.get("Rodent")).i++;
			if(o instanceof Gerbil)
				((Counter)map.get("Gerbil")).i++;
			if(o instanceof Hamster)
				((Counter)map.get("Hamster")).i++;				
		}
		// List each individual pet:
		for(int i = 0; i < pets.length; i++)
		System.out.println(pets[i].getClass());
		// Show the counts:
		System.out.println(map);
	}
}
