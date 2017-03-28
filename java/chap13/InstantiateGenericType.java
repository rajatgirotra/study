/*
 * Please read Must_Read_5.txt first
 */
class ClassAsFactory<T> {
	T x;
	public ClassAsFactory(Class<T> kind) {
		try {
			x = kind.newInstance();
		} catch(Exception e) {
			throw new RuntimeException(e);
		}
	}
}
class Employees {}

public class InstantiateGenericType {
	public static void main(String[] args) {
		ClassAsFactory<Employees> empRef = new ClassAsFactory<Employees>(Employees.class);
		ClassAsFactory<Integer> intRef = new ClassAsFactory<Integer>(Integer.class);	
		//The above will give u a run time exception as there is no default c'tor available for Integer
	}	
}

/*
 * So to overcome this you can use a variant of the Factory pattern in which instead of passing Integer.class you pass
 * IntegerFactory.factory() which takes care of creating the object for you.
 * Please read the next example for you to understand clearly.
 * Please read FactoryConstraint.java next
 */
