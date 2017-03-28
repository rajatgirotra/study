/*
 * Please read Must_Read_7.txt first
 */

import java.util.*;
public class SuperTypeWildcards {
	static void writeTo(List<? super Apple> apples) {
		apples.add(new Apple());
		apples.add(new Jonathan());
		apples.add(new Fruit()); //Error
	}
}

/*
The argument apples is a List of some type that is the base type of Apple; thus you know that it is safe 
to add an Apple or a subtype of Apple. Since the lower bound is Apple, however, you don’t know that it is safe 
to add Fruit to such a List, because that would allow the List to be opened up to the addition of non-Apple types, 
which would violate static type safety.
*/

/*
Please read SuperWildcard next
*/
