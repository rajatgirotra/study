import java.util.*;

class Cleanser {
	private String s = new String("Cleanser()");
	public void append(String s) {
		this.s += s;
	}

	public void dilute() {
		append(" dilute()");
	}
	public void apply() {
		append(" apply()");
	}
	public void scrub() {
		append(" scrub()");
	}
	public String toString() {
		return s;
	}
	public static void main(String[] args) {
		Cleanser c = new Cleanser();
		c.dilute(); c.apply(); c.scrub();
		System.out.println(c);
	}
}

class Detergent extends Cleanser {
	public void scrub() {
		append(" Detergent scrub()");
		super.scrub();
	}
	public void foam() {
		append(" foam()");
	}
	public static void main(String[] args) {
		Detergent d = new Detergent();
                d.dilute();
		d.apply();
		d.scrub();
		d.foam();
		System.out.println(d);
		Cleanser.main(args);
	}
}

/*
super that refers to the superclass that the current class has
been inherited from. Thus the expression super.scrub( ) calls the baseclass
version of the method scrub( ).
*/
