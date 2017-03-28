import java.util.*;

class Note {
	private String s;
	private Note(String s) {
		this.s = s;
	}
	public String toString() {
		return s;
	}
	public static final Note
		MIDDLE_C = new Note("MIDDLE_C"),
		C_SHARP  = new Note("C_SHARP"),
		B_FLAT   = new Note("B_FLAT");
}

class Instrument {
	public void play(Note n) {
		System.out.println("Instrument.play() - " + n);
	}
}

class Wind extends Instrument {
	public void play(Note n) {
		System.out.println("Wind.play() - " + n);
	}
	public static void tune(Instrument i) {
		i.play(Note.MIDDLE_C);
	}
}

public class Music {
	public static void main(String[] args) {
		Wind flute = new Wind();
		Instrument ins = new Instrument();
		Wind.tune(flute);
		Wind.tune(ins);
	}
}

/*
All method binding in Java uses late binding unless a method has been
declared final. This means that ordinarily you dont need to make any
decisions about whether late binding will occurit happens
automatically. Feedback
Why would you declare a method final? As noted in the last chapter, it
prevents anyone from overriding that method. Perhaps more important, it
effectively turns off dynamic binding, or rather it tells the compiler that
dynamic binding isnt necessary. This allows the compiler to generate
slightly more efficient code for final method calls. However, in most
cases it wont make any overall performance difference in your program,
so its best to only use final as a design decision, and not as an attempt to
improve performance.
*/
