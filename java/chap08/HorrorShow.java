/*
please read Music5.java first
*/
import java.util.*;

interface Monster {
	void menace();
}

interface DangerousMonster extends Monster {
	void destroy();
}

interface Lethal {
	void kill();
}

class DragonZilla implements DangerousMonster {
	public void menace() {
		System.out.println("DragonZilla::menace");
	}
	
	public void destroy() {
		System.out.println("DragonZilla::destroy");
	}
	
	public void placeHolder() {
		System.out.println("DragonZilla::placeHolder");
	}
}

/* an interface can extend one or more interfaces */
interface Vampire extends DangerousMonster, Lethal {
	void drinkBlood();
}

/* Class VeryBadVampire must implement all functions implemented by Vampire and its super interfaces. */
class VeryBadVampire implements Vampire {	
	public void menace() {
		System.out.println("VeryBadVampire::menace");
	}
	public void destroy() {
		System.out.println("VeryBadVampire::destroy");
	}
	public void kill() {
		System.out.println("VeryBadVampire::kill");
	}
	public void drinkBlood() {
		System.out.println("VeryBadVampire::drinkBlood");
	}	
}

public class HorrorShow {
	static void u(Monster b) { b.menace(); }
	static void v(DangerousMonster d) { 
		d.menace();
		d.destroy();
	}
	static void w(Lethal l) { l.kill(); }
	public static void main(String[] args) {
		DangerousMonster barney = new DragonZilla();
		u(barney);
		v(barney);
		Vampire vlad = new VeryBadVampire();
		u(vlad);
		v(vlad);
		w(vlad);
		
		vlad.drinkBlood();
	}	
}
/*
Please read NestingInterfaces.java next
*/