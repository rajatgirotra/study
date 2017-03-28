import java.util.*;

class P2 {
	void play() {
		System.out.println("P2.play()");
	}
}

class P1 extends P2 {
	void play() {
		System.out.println("P1.play()");
		super.play();
	}
	public static void main(String[] args) {
		P2 p2 = new P1();
		p2.play();
	}
}

