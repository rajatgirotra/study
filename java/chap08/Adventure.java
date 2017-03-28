/*
 * First file in this project
 */
import java.util.*;

interface CanFight {
	void fight();	
}

interface CanSwim {
	void swim();	
}

interface CanFly {
	void fly();
}

class ActionCharacter {
	public void fight() {
		System.out.println("ActionCharacter::fight()");
	}
}

class Hero extends ActionCharacter
				implements CanFight, CanSwim, CanFly {
	public void swim() {
		System.out.println("Hero::swim()");
	}
	public void fly() {
		System.out.println("Hero::fly()");
	}
	
	/*	
	public void fight() {
		System.out.println("Hero::fight()");
	}
	*/
	
}
public class Adventure {

	/**
	 * @param args
	 */
	public static void t(CanFight x) {
		x.fight();
	}
	public static void u(CanSwim x) {
		x.swim();
	}
	public static void v(CanFly x) {
		x.fly();
	}
	public static void w(ActionCharacter x) {
		x.fight();
	}
	public static void main(String[] args) {
		Hero h = new Hero();
		t(h);
		u(h);
		v(h);
		w(h);
	}
}

/*
 When you combine a concrete class with interfaces this way, the concrete class must
come first, then the interfaces. (The compiler gives an error otherwise.)

Note that the signature for fight( ) is the same in the interface
CanFight and the class ActionCharacter, and that fight( ) is not
provided with a definition in Hero. The rule for an interface is that you
can inherit from it (as you will see shortly), but then you’ve got another
interface. If you want to create an object of the new type, it must be a
class with all definitions provided. Even though Hero does not explicitly
provide a definition for fight( ), the definition comes along with
ActionCharacter so it is automatically provided and it’s possible to
create objects of Hero.

An
interface gives you the benefits of an abstract class and the benefits of
an interface, so if it’s possible to create your base class without any
method definitions or member variables you should always prefer
interfaces to abstract classes. In fact, if you know something is going to
be a base class, your first choice should be to make it an interface, and
only if you’re forced to have method definitions or member variables
should you change to an abstract class, or if necessary a concrete class.

Also try to comment out Hero::fight() method and see what happens.

Please read Must_read_1.txt next.
*/
