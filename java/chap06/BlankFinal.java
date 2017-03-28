/*
Java allows the creation of blank finals, which are fields that are declared
as final but are not given an initialization value. In all cases, the blank
final must be initialized before it is used, and the compiler ensures this.
However, blank finals provide much more flexibility in the use of the
final keyword since, for example, a final field inside a class can now be
different for each object and yet it retains its immutable quality. Heres an
example.
*/

import java.util.*;

class Poppet {
	private int i;
	public Poppet(int i) {
		this.i = i;
	}
}

class BlankFinal {
	private final int j = 0; //Initialised final.
	private final int k; //Blank final
	private final Poppet p; //blank final reference

	BlankFinal() {
		k = j;
		p = new Poppet(k);		
	}

	BlankFinal(int i) {
		k = i;
		p = new Poppet(k);
	}
	public static void main(String[] args) {
		new BlankFinal();
		new BlankFinal(78);
	}
}

/*
Youre forced to perform assignments to finals either with an expression
at the point of definition of the field or in every constructor. That way its
guaranteed that the final field is always initialized before use
*/
