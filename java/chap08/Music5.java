/*
 * Please read TestMonths.java first
 */

/**
 * @author RGirotra
 *
 */

interface Instrument {
	int i = 5; //implicitly static & final
	void play();
	String what();
}

class Wind implements Instrument {
	public void play() {
		System.out.println(Integer.toString(i));
		System.out.println("Wind::play()");
	}
	public String what() {
		return "Wind";
	}
}

class Percussion implements Instrument {
	public void play() {
		System.out.println("Percussion::play()");
	}
	public String what() {
		return "Percussion";
	}
}

class Brass extends Wind {
	public String what() {
		System.out.println(Integer.toString(i));
		//++i;
		return "Brass";
	}
}
public class Music5 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Instrument ins = new Brass();
		System.out.println(ins.what());
		ins.play();
	}
}

/*
please read horrorshow.java next
*/