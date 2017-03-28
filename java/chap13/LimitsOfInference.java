/*
 * Please read New.java first.
 */
import java.util.List;
import java.util.Map;

public class LimitsOfInference {
	public static void foo(Map<String, List<String>> map) {		
	}
	
	public static void main(String[] args) {
		//foo(New.map()); //Please uncomment this line.
        //the method foo(Map<String,List<String>>) in the type LimitsOfInference is not applicable for the arguments (Map<Object,Object>)
	}
}

/*
Please read ExplicitTypeSpecification.java next
*/