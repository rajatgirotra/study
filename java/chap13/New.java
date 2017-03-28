/*
 * Please read GenericMethods.java first
 * Some people think that generics mandate a lot of keystrokes. For example to create a Map of Pets & People you have to say
 * Map<Person, List<? extends Pet>> myMap = new HashMap<Person, List<? extends Pet>>();
 * To avoid this you can create some utility tools using Generic Methods. See below:
 */
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

public class New {
	public static <K,V> Map<K,V> map() {
		return new HashMap<K,V>();
	}
	
	public static <T> List<T> list() {
		return new ArrayList<T>();
	}
	
	public static <T> LinkedList<T> llist() {
		return new LinkedList<T>();
	}
	
	public static <T> Set<T> set() {
		return new HashSet<T>();
	}
	
	public static <T> Queue<T> queue() {
		return new LinkedList<T>();
	}
	
	@SuppressWarnings("unused")
	public static void main(String[] args) {
		Map<String, List<String>> map = New.map();
		List<String> ls = New.list();
		LinkedList<String> lls = New.llist();
		Set<String> ss = New.set();
		Queue<String> qs = New.queue();
	}
}

/*
You can see that New.map() has automatically inferred the type of Map key and value to create.
Similarly for the other functions. But this Type inference happens only while making an assignment.
I mean if New.map() is passed as an argument to a function, which accepts <String, List<String>> then type inference will
not happen and the compiler will complain. This is the limitation of type inference.

Please read LimitsOfInference.java next
*/