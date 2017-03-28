/*
 * Please read TupleTest2.java first.
 */

class Elephant {	
}

class Employee {	
}

class Mirror {	
}

/*
 * Three totally unrelated classes above
 */
public class TupleTest {
	public static FiveTuple<Elephant, Employee, Mirror, String, Integer> ft() {
		return new FiveTuple<Elephant, Employee, Mirror, String, Integer> 
						(new Elephant(), new Employee(), new Mirror(), new String("ABCD"), new Integer(10));
	}
	public static void main(String[] args) {
		System.out.println(ft());
	}
}

/*
Please read Sets.java first
*/