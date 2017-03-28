import java.util.*;

abstract class Glyph {
	abstract void draw();
	Glyph() {
		System.out.println("Glyph() before draw()");
		draw();
		System.out.println("Glyph() after draw()");
	}
	
	static {
		System.out.println("Glyph static block");
	}
	{
		System.out.println("Glyph non-static block");
	}
	
}
class RoundGlyph extends Glyph {
	private int radius = 1;
	RoundGlyph(int r) {
		radius = r;
		System.out.println("RoundGlyph.RoundGlyph(), radius = " + radius);
	}
	void draw() {
		System.out.println(
				"RoundGlyph.draw(), radius = " + radius);
	}
	static {
		System.out.println("RoundGlyph static block");
	}
	{
		System.out.println("RoundGlyph nonstatic block");
	}

	
}
public class PolyConstructors {
	public static void main(String[] args) {
		new RoundGlyph(5);
	}
}

/*
In Glyph, the draw( ) method is abstract, so it is designed to be
overridden. Indeed, you are forced to override it in RoundGlyph. But
the Glyph constructor calls this method, and the call ends up in
RoundGlyph.draw( ), which would seem to be the intent. But if you
look at the output, you can see that when Glyphs constructor calls
draw( ), the value of radius isnt even the default initial value 1. Its 0.
This would probably result in either a dot or nothing at all being drawn on
the screen, and youd be left staring, trying to figure out why the program
wont work.

The order of initialization described in the earlier section isnt quite
complete, and thats the key to solving the mystery. The actual process of
initialization is:

AS DESCRIBED IN FILE ClassInitialization.java

As a result, a good guideline for constructors is, Do as little as possible to
set the object into a good state, and if you can possibly avoid it, dont call
any methods. The only safe methods to call inside a constructor are those
that are final in the base class. (This also applies to private methods,
which are automatically final.) These cannot be overridden and thus
cannot produce this kind of surprise.

*/
