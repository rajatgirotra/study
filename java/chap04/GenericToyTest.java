/*
   Please read GenericClassReferences.java first.
*/

interface HasBatteries {}
interface Waterproof {}
interface Shoots {}

class Toy {
	// Comment out the following default constructor
	// to see NoSuchMethodError from (*1*)
	Toy() {}
	Toy(int i) {}
}

class FancyToy extends Toy implements HasBatteries, Waterproof, Shoots {
	FancyToy() { super(1); }
}


public class GenericToyTest {
    public static void main(String[] args) throws Exception {
        Class<FancyToy> ftClass = FancyToy.class;
        // Produces exact type:
        FancyToy fancyToy = ftClass.newInstance();
        Class<? super FancyToy> up = ftClass.getSuperclass();
        // This wont compile:
        Class<Toy> up2 = ftClass.getSuperclass(); // --->> A
        // Only produces Object: not a reference to a Toy.
        Object obj = up.newInstance();
        Toy t = up.newInstance(); //Not possible too!!
        //unless you cast it.
        Toy t1 = (Toy) up.newInstance();
    }
}

/*
it is strange that even though the compiler knows at compile time that the superclass of FancyToy is Toy it does not allow you to directly use it in A. If you look at the definition of this function in the JAVA doc it is,

public Class<? super T> getSuperclass()

that is why you must say

Class<? super FancyToy> cls = ftClass.getSuperclass();

*/

