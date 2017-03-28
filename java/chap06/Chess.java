/*
If your class doesnt have default
arguments, or if you want to call a base-class constructor that has an
argument, you must explicitly write the calls to the base-class constructor
using the super keyword and the appropriate argument list:
*/

import java.util.*;

class Game {
	Game(int i) {
		System.out.println("Game c'tor");
	}
}

class BoardGame extends Game {
	BoardGame(int i) {
		super(i);
		System.out.println("BoardGame c'tor");		
	}
}

class Chess extends BoardGame {
	Chess() {
		//super(11);
		System.out.println("Chess c'tor");
	}
	public static void main(String[] args) {
		Chess c = new Chess();
	}
}

/*
If you dont call the base-class constructor in BoardGame( ), the
compiler will complain that it cant find a constructor of the form
Game( ). In addition, the call to the base-class constructor must be the
first thing you do in the derived-class constructor. (The compiler will
remind you if you get it wrong.)
*/
