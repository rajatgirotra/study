/*
 * Please read UniqueWords.java first
 * Simple demonstration of JAVA Map functions get() and put(), containsKey() & containsValue()
 */
import typeinfo.pets.*;
import java.util.*;
import static com.rajatgirotra.util.Print.*;
public class PetMap {
	public static void main(String[] args) {
		Map<String,Pet> petMap = new HashMap<String,Pet>();
		petMap.put("My Cat", new Cat("Molly"));
		petMap.put("My Dog", new Dog("Ginger"));
		petMap.put("My Hamster", new Hamster("Bosco"));
		print(petMap);
		Pet dog = petMap.get("My Dog");
		print(dog);
		print(petMap.containsKey("My Dog"));
		print(petMap.containsValue(dog));
	}
}
/*
Please read MapOfList.java next
*/