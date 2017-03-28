/*
 * Please read Erased.java first
 */

class Building { }
class House extends Building {}

public class ClassTypeCapture<T> {
	private Class<T> kind;
	private ClassTypeCapture(Class<T> type) {
		kind = type;
	}
	
	public boolean f(Object arg) {
		return kind.isInstance(arg);
	}
	
	public static void main(String[] args) {
		ClassTypeCapture<Building> b = new ClassTypeCapture<Building>(Building.class);
		System.out.println(b.f(new Building()));
		System.out.println(b.f(new House()));
		
		ClassTypeCapture<House> h = new ClassTypeCapture<House>(House.class);
		System.out.println(h.f(new Building()));
		System.out.println(h.f(new House()));		
	}	
}

/*
Please read Must_Read_5.txt next
*/