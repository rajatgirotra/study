/*
Please read GenericToyTest.java first
*/

/*
JAVA SE 5 adds a new cast() method to the Class class.
The cast( ) method takes the argument object and casts it to the type of the Class reference.
*/

import java.util.*;

class Building {
}

class House extends Building {
}

class Unrelated {
}


class ClassCasts {
	public static void main(String[] args) {
		Building b = new House();
		Unrelated ur = new Unrelated();
		Class<House> houseClass = House.class;
		House h = houseClass.cast(b);
		House h1 = houseClass.cast(ur); //will generate ClassCastException.
		 //House h2 = (House)b; //or just do this
		 //House h3 = (House)ur;
	}
}

/*
The reason of introducing the cast() method was to use it while using generics
*/

