import java.util.ArrayList;
import java.util.List;

/*
 * Please read ExplicitTypeSpecification.java first.
 * Generics and Var args methods coexist nicely. If a methods takes repeated but unknown number of the same argument; you 
 * can achieve that simply by noting the below syntax.
 */
public class GenericVarargs {
	public static <T> List<T> makeList(T... args) {
		List<T> l = new ArrayList<T>();
		for(T item : args) {
			l.add(item);
		}
		return l;
	}
	
	public static void main(String[] args) {
		System.out.println(makeList("A"));
		System.out.println(makeList(("ABCDEFGHIJKLMNOPQRSTUVWXYZ").split("")));
	}
}

/*
Please read Generators.java next
*/