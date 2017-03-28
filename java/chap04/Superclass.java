class A {}
class B extends A {}
interface C {}

public class Superclass {
	public static void main(String[] args) {
		Class<?> c = null;
		c = A.class.getSuperclass();
		System.out.println("Super class of A: " + c.getName());
		c = B.class.getSuperclass();
		System.out.println("Super class of B: " + c.getName());
		c = C.class.getSuperclass();
		System.out.println("Super class of C: " + (c == null ? "null" : c.getName()));
		c = int.class.getSuperclass();
		System.out.println("Super class of primitive int: " + (c == null ? "null" : c.getName()));
		c = int[].class.getSuperclass();
		System.out.println("Super class of array: " + (c == null ? "null" : c.getName()));
		c = void.class.getSuperclass();
		System.out.println("Super class of void: " + (c == null ? "null" : c.getName()));
	}
}
