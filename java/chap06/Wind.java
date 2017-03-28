import java.util.*;

class Instrument {
	public void play() {
		System.out.println("Instrument::play()");
	}

	static void tune(Instrument i) {
		i.play();
	}
}

public class Wind extends Instrument {
	public void play() {
		System.out.println("Wind::play()");
	}

	public static void main(String[] args) {
		Wind flute = new Wind();
		Instrument.tune(flute);
	}
}
	


/*
Whats interesting in this example is the tune( ) method, which accepts
an Instrument reference. However, in Wind.main( ) the tune( )
method is called by giving it a Wind reference. Given that Java is
particular about type checking, it seems strange that a method that
accepts one type will readily accept another type, until you realize that a
Wind object is also an Instrument object, and theres no method that
tune( ) could call for an Instrument that isnt also in Wind. Inside
tune( ), the code works for Instrument and anything derived from
Instrument, and the act of converting a Wind reference into an
Instrument reference is called upcasting.
*/
