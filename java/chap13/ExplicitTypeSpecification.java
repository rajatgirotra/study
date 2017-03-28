import java.util.List;
import java.util.Map;

/*
 * Please read LimitsOfInference.java first
 * It is possible to explicitly specify the types when making a generic method call. When doing this you have to place the 
 * types inside angle brackets after the dot and before the function name. For calling static generic methods, place the types
 * after the class name and dot. For calling methods within the same class use this.<types>foo(); 
 */
public class ExplicitTypeSpecification {
	public static void foo(Map<String, List<String>> map) {		
	}
	
	public static void main(String[] args) {
		foo(New.<String, List<String>>map()); // Note the syntax as explained above.
	}
}

/*
Please read GenericVarargs.java next
*/