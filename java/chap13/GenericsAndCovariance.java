/*
 * Please read NonCovariantGenerics.java first
 */

/*
Sometimes, however, you’d like to establish some kind of upcasting relationship between the two. This is 
what wildcards allow.
 */
import java.util.*;
public class GenericsAndCovariance {
	public static void main(String[] args) {
		// Wildcards allow covariance:
		List<? extends Fruit> flist = new ArrayList<Apple>();
		// Compile Error: can’t add any type of object:
		flist.add(new Apple());
		// flist.add(new Fruit());
		// flist.add(new Object());
		flist.add(null); // Legal but uninteresting
		// We know that it returns at least Fruit:
		Fruit f = flist.get(0);		
	}
}
/*
The type of flist is now List<? extends Fruit>, which you can read as "a list of any type that’s inherited from Fruit." 
This doesn’t actually mean that the List will hold any type of Fruit, however. The wildcard refers to a definite type, 
so it means "some specific type which the flist reference doesn’t specify." So the List that’s assigned has to be holding 
some specified type such as Fruit or Apple, but in order to upcast to flist, that type is a "don’t actually care.

The type of flist is now List<? extends Fruit>, which you can read as "a list of any type that’s inherited from Fruit." 
This doesn’t actually mean that the List will hold any type of Fruit, however. The wildcard refers to a definite type, 
so it means "some specific type which the flist reference doesn’t specify." So the List that’s assigned has to be holding 
some specified type such as Fruit or Apple, but in order to upcast to flist, that type is a "don’t actually care."
If the only constraint is that the List hold a specific Fruit or subtype of Fruit, but you don’t actually care what it is, 
then what can you do with such a List? If you don’t know what type the List is holding, how can you safely add an object? 
Just as with the "upcast" array in CovariantArrays.java, you can’t, except that the compiler prevents it from happening rather 
than the runtime system. You discover the problem sooner.

You might argue that things have gone a bit overboard, because now you can’t even add an Apple to a List that you just said would 
hold Apples. Yes, but the compiler doesn’t know that. A List<? extends Fruit> could legally point to a List<Orange>. Once you do 
this kind of "upcast," you lose the ability to pass anything in, even an Object.

On the other hand, if you call a method that returns Fruit, that’s safe because you know that anything in the List must at least be 
of type Fruit, so the compiler allows it.
*/

/*
Please read CompilerIntelligence.java next
*/