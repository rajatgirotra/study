/*
 * Please read EpicBattle.java first.
 */

class Fruit { }
class Apple extends Fruit {}
class Orange extends Fruit {}
class Jonathan extends Apple {}


public class CovariantArrays {
	public static void main(String[] args) {
		Fruit[] fruit = new Apple[10];
		fruit[0] = new Apple();
		try {
			fruit[1] = new Jonathan();
		}catch(Exception e) {
			System.out.println(e);
		}
		try {
			fruit[2] = new Fruit();
		} catch(Exception e) {
			System.out.println(e);
		}
		try {
			fruit[3] = new Orange();
		} catch(Exception e) {
			System.out.println(e);
		}	 
	}
}

/*
A base class array reference can point to a derived class array. So
		Fruit[] fruit = new Apple[10];
is valid.
But since an array always remembers its original type (the type with which it was created)

		fruit[2] = new Fruit();
		fruit[2] = new Orange();
are invalid and are caught at run time.
But the compiler does not produce a warning here beacuse fruit[] is of type Fruit[], 
so a base class ref can hold a derived class object.



The first line in main( ) creates an array of Apple and assigns it to a reference to an array of Fruit. 
This makes sense—an Apple is a kind of Fruit, so an array of Apple should also be an array of Fruit.
However, if the actual array type is Apple [], you should only be able to place an Apple or a subtype of 
Apple into the array, which in fact works at both compile time and run time. But notice that the compiler 
allows you to place a Fruit object into the array. This makes sense to the compiler, because it has a Fruit[] 
reference—why shouldn’t it allow a Fruit object, or anything descended from Fruit, such as Orange, to be 
placed into the array? So at compile time, this is allowed. The runtime array mechanism, however, knows that 
it’s dealing with an Apple [] and throws an exception when a foreign type is placed into the array.

Please read NonCovariantGenerics.java next

*/