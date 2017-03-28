import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.TreeSet;

/*
 * Please read WatercolorSets.java first
 * This is an extremely good program. This uses Sets.difference() to display the difference in the 
 * methods() of Collection & Map interfaces.
 */
public class ContainerMethodDifferences {
	//Generic static method which returns a Set of methods() defined in a class.
	public static Set<String> methodSet(Class<?> type) {
		Set<String> set = new TreeSet<String>();
		for(Method m : type.getMethods()) {
			set.add(m.getName());
		}
		return set;
	}

	//Generic static method that returns a List of interfaces() implemented by this class.
	public static void interfaces(Class<?> type) {
		List<String> list = new ArrayList<String>();
		for(Class<?> c : type.getInterfaces()) {
			list.add(c.getSimpleName());
		}
		System.out.println(list);		
	}

	//store all the methods provided by Object
	static Set<String> object = methodSet(Object.class);
	static { object.add("clone"); }
	//Note a very important point; The order of initialization of statics is the order in which 
	//they are declared in the class. If you toggle the above two statements you can see this for
	//yourself.

	//Calculate the differences
	static void difference(Class<?> subClass, Class<?> superClass) {
		System.out.println("Class " + subClass.getSimpleName() + " extends Class " + superClass.getSimpleName());
		Set<String> diff = Sets.difference(methodSet(subClass), methodSet(superClass));
		diff.removeAll(object);
		System.out.println(diff);
		interfaces(superClass);
	}

	public static void main(String[] args) {
		System.out.println("Collection: " + methodSet(Collection.class));
		interfaces(Collection.class);
		difference(Set.class, Collection.class);
		difference(HashSet.class, Set.class);
		difference(LinkedHashSet.class, HashSet.class);
		difference(TreeSet.class, Set.class);
		difference(List.class, Collection.class);
		difference(ArrayList.class, List.class);
		difference(LinkedList.class, List.class);
		difference(Queue.class, Collection.class);
		difference(PriorityQueue.class, Queue.class);
		System.out.println("Map: " + methodSet(Map.class));
		difference(HashMap.class, Map.class);
		difference(LinkedHashMap.class, HashMap.class);
		difference(SortedMap.class, Map.class);
		difference(TreeMap.class, Map.class);
	}
}

/*
Please read BankTeller.java next
*/