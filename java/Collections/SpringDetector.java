/* Please read Must_Read_3.java first */
/* Use of hashCode() when using Maps */
/* Object.equals() method only compares object addresses */
/* i.e. two objects are equal if they point to the same object */
/* Same behavior is achieved by == */

import java.lang.reflect.Constructor;
import java.util.LinkedHashMap;
import java.util.Map;

class Groundhog {
	protected int number;
	public Groundhog(int number) {
		this.number = number;
	}
	
	public String toString() {
		return "Groundhog# " + number;
	}
}

class Prediction {
	public boolean shadow = Math.random() > 0.5;
	public String toString() {
		if(shadow == true)
			return "Six more months of winter";
		else
			return "Spring season soon..!!";
	}
}

class Groundhog2 extends Groundhog {
	public Groundhog2(int number) {
		super(number);
	}
	public boolean equals(Object o) {
		return ((o instanceof Groundhog2) && (number == ((Groundhog2)o).number));
	}
	public int hashCode() {
		return number;
	}
}

public class SpringDetector {
	@SuppressWarnings("unchecked")
	public static void detectSpring(Class cls) throws Exception {
		Map m = new LinkedHashMap();
		Constructor ctor = cls.getConstructor(new Class[] {int.class});
		Groundhog ghog = null;
		
		for(int i = 0; i < 10; ++i) {
			ghog = (Groundhog)ctor.newInstance(new Object[] {new Integer(i)});
			m.put(ghog, new Prediction());
		}
		
		System.out.println("Map: " + m);
		Groundhog gh = (Groundhog)ctor.newInstance(new Object[] {new Integer(3)});
		if(m.containsKey(gh)) {
			System.out.println(m.get(gh));			
		}
		else {
			System.out.println("Key not found");
		}
	}
	
	public static void main(String[] args) throws Exception {
		//SpringDetector.detectSpring(Groundhog.class);
		SpringDetector.detectSpring(Groundhog2.class);
	}

}

/*
The problem is that Groundhog is inherited from the common root class Object (which is
what happens if you don’t specify a base class, thus all classes are ultimately inherited from Object).
It is Object’s hashCode( ) method that is used to generate the hash code for each object, and by 
default it just uses the address of its object. Thus, the first instance of Groundhog(3) does not 
produce a hash code equal to the hash code for the second instance of Groundhog(3) that we tried to use 
as a lookup.

You might think that all you need to do is write an appropriate override
for hashCode( ). But it still won’t work until you’ve done one more
thing: override the equals( ) that is also part of Object. equals( ) is
used by the HashMap when trying to determine if your key is equal to
any of the keys in the table. Again, the default Object.equals( ) simply
compares object addresses, so one Groundhog(3) is not equal to
another Groundhog(3).

Thus, to use your own classes as keys in a HashMap, you must override
both hashCode( ) and equals( ).

Please read Statistics.java next
*/