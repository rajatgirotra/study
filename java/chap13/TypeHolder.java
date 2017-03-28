/*
 * Please read CompilerIntelligence.java first
 */
public class TypeHolder<T> {
	private T value;
	TypeHolder(T item) {
		value = item;
	}
	public T get() {
		return value;
	}
	public void set(T item) {
		value = item;
	}
	public boolean equals(Object obj) {
		return value.equals(obj);
	}

	public static void main(String[] args) {
		TypeHolder<Apple> app = new TypeHolder<Apple>(new Apple());
		Apple d = app.get();
		app.set(d);
		// TypeHolder<Fruit> Fruit = app; // Cannot upcast
		TypeHolder<? extends Fruit> fruit = app; // OK
		Fruit p = fruit.get();
		d = (Apple)fruit.get(); // Returns ‘Object’
		try {
			Orange c = (Orange)fruit.get(); // No warning
		} catch(Exception e) { System.out.println(e); }
		// fruit.set(new Apple()); // Cannot call set()
		// fruit.set(new Fruit()); // Cannot call set()
		System.out.println(fruit.equals(d)); // OK
	}
}

/*
TypeHolder has a set() which takes a T, a get() which returns a T, and an equals() that takes an Object. As you’ve already seen, 
if you create a TypeHolder<Apple>, you cannot upcast it to a TypeHolder<Fruit>, but you can upcast to a TypeHolder<? extends Fruit>. 
If you call get(), it only returns a Fruit—that’s as much as it knows given the "anything that extends Fruit" bound. If you know more 
about what’s there, you can cast to a specific type of Fruit and there won’t be any warning about it, but you risk a ClassCastException. 
The set() method won’t work with either an Apple or a Fruit, because the set() argument is also "? Extends Fruit," which means it can be 
anything and the compiler can’t verify type safety for "anything."

However, the equals( ) method works fine because it takes an Object instead of a T as an argument. 
Thus, the compiler is only paying attention to the types of objects that are passed and returned. It is not analyzing the code to 
see if you perform any actual writes or reads.

*/

/*
Please read Must_Read_7.txt
*/