/*
   Final arguments
   Java allows you to make arguments final by declaring them as such in the
   argument list. This means that inside the method you cannot change what
   the argument reference points to:
 */

//: c06:FinalArguments.java
// Using "final" with method arguments.
class Gizmo {
	public void spin() {}
}
public class FinalArguments {
	void with(final Gizmo g) {
		  g = new Gizmo(); // Illegal -- g is final
	}

	void without(Gizmo g) {
		g = new Gizmo(); // OK -- g not final
		g.spin();
	}

	// void f(final int i) { i++; } // Can't change
	// You can only read from a final primitive:
	int g(final int i) { return i + 1; }

	public static void main(String[] args) {
		FinalArguments bf = new FinalArguments();
		bf.without(null);
		bf.with(null);
	}
} ///:~

/*
   The methods f( ) and g( ) show what happens when primitive arguments
   are final: you can read the argument, but you can't change it.
 */
