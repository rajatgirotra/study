/*
 * Please read asListInterface.java first
 */

import java.util.*;

public class PrintingContainers {
	private static Collection<String> fill(Collection<String> stringColl) {
		stringColl.add("Cat");
		stringColl.add("Dog");
		stringColl.add("Cow");
		stringColl.add("Rat");
		stringColl.add("Cow");
		stringColl.add("Dog");
		stringColl.add("Cat");
		stringColl.add("Rat");
		return stringColl;
	}
	
	private static Map<String, String> fill(Map<String, String> strMap) {
		strMap.put("Dog", "Scooby");
		strMap.put("Rat", "Stuart Little");
		strMap.put("Cat", "Kitty");
		strMap.put("Cow", "Gaya");
		strMap.put("Dog", "Breezer"); // the previous value gets updated.
		return strMap;
	}
	
	public static void main(String[] args) {
		System.out.println("ArrayList: " + fill(new ArrayList<String>()));
		System.out.println("LinkedList: " + fill(new LinkedList<String>()));
		System.out.println("HashSet: " + fill(new HashSet<String>()));
		System.out.println("TreeSet: " + fill(new TreeSet<String>()));
		System.out.println("LinkedHashSet: " + fill(new LinkedHashSet<String>()));
		System.out.println("HashMap" + fill(new HashMap<String, String>()));
		System.out.println("TreeMap" + fill(new TreeMap<String, String>()));
		System.out.println("LinkedHashMap" + fill(new LinkedHashMap<String, String>()));
	}
}

/*
Please read SimpleIteration.java next
*/