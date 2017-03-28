/*
 * Please read GenericsAndCovariance.java first
 */
/*
 Now, you might guess that you are prevented from calling any methods that take arguments,
 but consider this
 */
import java.util.Arrays;
import java.util.List;

public class CompilerIntelligence {
	public static void main(String[] args) {
		List<? extends Fruit> flist = Arrays.asList(new Apple(), new Orange());
		Apple a = (Apple)flist.get(0); // No warning
		flist.contains(new Apple()); // Argument is ‘Object’
		flist.indexOf(new Apple()); // Argument is ‘Object’
	}
}

/*
You can see calls to contains( ) and indexOf( ) that take Apple objects as arguments, and those are just fine.
By looking at the documentation for ArrayList, we find that the compiler is not that smart. While add( ) takes 
an argument of the generic parameter type, contains( ) and indexOf( ) take arguments of type Object. 
So when you specify an ArrayList <? extends Fruit >, the argument for add( ) becomes’? extends Fruit’. 
From that description, the compiler cannot know which specific subtype of Fruit is required there, 
so it won’t accept any type of Fruit. It doesn’t matter if you upcast the Apple to a Fruit first—the compiler simply 
refuses to call a method (such as add( )) if a wildcard is involved in the argument list. 

With contains( ) and indexOf( ), the arguments are of type Object, so there are no wildcards involved and the compiler 
allows the call. This means that it’s up to the generic class designer to decide which calls are "safe," and to use Object 
types for their arguments. To disallow a call when the type is used with wildcards, use the type parameter in the argument list.

*/

/*
Please read TypeHolder.java next
*/