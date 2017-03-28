/*
 * Please read CovariantArrays.java first.
 */
// {CompileTimeError} (Won’t compile)
import java.util.*;

public class NonCovariantGenerics {
	// Compile Error: incompatible types:
	List<Fruit> flist = new ArrayList<Apple>();
}

/*  
The following is very important. Read it very carefully. You have understood this before; so you should
not have a problem reading and understanding it again.

When you see the above error: you might say to yourself that "You cannot assign a container of apples to
a container of fruits. BUT dont look at it this way. Look at it from the point of view of generics. The actual
issue is that "YOU CANT ASSIGN A GENERIC INVOLVING APPLES TO A GENERIC INVOLVING FRUITS".
								OR
A list of apples is not a list of fruits. A list of apples will only contain apples or any subtypes of apples.
Similarly a list of Fruits will only hold fruits or any subtype of  fruits (apples, oranges) etc.. but that does
not make it a list of apples. It still remains a list of fruits.

A List of Apple is not type-equivalent to a List of Fruit, even if an Apple is a type of Fruit.

Please read GenericsAndCovariance.java next
*/
