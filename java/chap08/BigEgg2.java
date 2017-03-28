/*
 * BigEgg.java first
 */
import java.util.*;

class Egg2 {
	protected class Yolk {
		public Yolk() { System.out.println("Egg2.Yolk()"); }
		public void f() { System.out.println("Egg2.Yolk.f()");}
	}
	private Yolk y = new Yolk();
	public Egg2() { System.out.println("New Egg2()"); }
	public void insertYolk(Yolk yy) { y = yy; }
	public void g() { y.f(); }
}
public class BigEgg2 extends Egg2 {
		public class Yolk extends Egg2.Yolk {
		public Yolk() { System.out.println("BigEgg2.Yolk()"); }
		public void f() {
			System.out.println("BigEgg2.Yolk.f()");
		}
	}
	public BigEgg2() { insertYolk(new Yolk()); }
	public static void main(String[] args) {
		Egg2 e2 = new BigEgg2();
		e2.g();
	}
} ///:~



/*
Now BigEgg2.Yolk explicitly extends Egg2.Yolk and overrides its
methods. The method insertYolk( ) allows BigEgg2 to upcast one of its
own Yolk objects into the y reference in Egg2, so when g( ) calls y.f( )
the overridden version of f( ) is used. The second call to Egg2.Yolk( ) is
the base-class constructor call of the BigEgg2.Yolk constructor. You can
see that the overridden version of f( ) is used when g( ) is called.

Last file in this chapter
*/
