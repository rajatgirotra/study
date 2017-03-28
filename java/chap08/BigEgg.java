/*
 * Overriding inner classes.
 * AnonymousContructor.java first
 */

class Egg {
	protected class Yolk {
		Yolk() {
			System.out.println("Egg::Yolk() c'tor");
		}		
	}
	private Yolk y;
	Egg() {
		System.out.println("Egg() c'tor");
		y = new Yolk();
	}
}

public class BigEgg extends Egg {
	class Yolk {
		public Yolk() {
			System.out.println("BigEgg::Yolk c'tor");
		}
	}
	BigEgg() {
		System.out.println("BigEgg c'tor");
	}
	
	public static void main(String[] args) {
		new BigEgg();
	}	
}

/*
 * This example shows that there isn’t any extra inner class magic going on
when you inherit from the outer class. The two inner classes are
completely separate entities, each in their own namespace

BigEgg2.java next
*/
