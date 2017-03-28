/*
 * Please read InheritBounds.java first
 * I am writing this myself to understand thoroughly bounded inheritance.
 */

interface SuperPower {}

interface XRayVision extends SuperPower {
	public void seeThroughWalls();
}
interface SuperHearing extends SuperPower {
	public void hearSubtleNoises();
}
interface SuperSmell extends SuperPower {
	public void trackBySmell();
}

class SuperHero<POWER extends SuperPower> {
	private POWER power;
	SuperHero(POWER power) {
		this.power = power;
	}
	public POWER getPower() {
		return power;
	}
}

class SuperSleuth<POWER extends XRayVision> extends SuperHero<POWER> {
	SuperSleuth(POWER power) {
		super(power);
	}
	
	void see() {
		getPower().seeThroughWalls();
	}
}

class CanineHero<POWER extends SuperHearing & SuperSmell> extends SuperHero<POWER> {
	CanineHero(POWER power) {
		super(power);
	}
	
	void hear() {
		getPower().hearSubtleNoises();
	}
	void smell() {
		getPower().trackBySmell();
	}
}

class SuperHearSmell implements SuperHearing, SuperSmell {
	public void hearSubtleNoises() {
		System.out.println("I can hear a very quite hush too..!!");
	}
	public void trackBySmell() {
		System.out.println("I can smell fish from 1 mile away..!!");
	}
}

class XRayMan implements XRayVision {
	public void seeThroughWalls() {
		System.out.println("I can also see through walls..!!");
	}
}

class DogBoy extends CanineHero<SuperHearSmell> {
	DogBoy() {
		super(new SuperHearSmell());
	}
}

class DogWomen extends SuperSleuth<XRayMan> {
	DogWomen() {
		super(new XRayMan());
	}
}

public class EpicBattle {
	static <POWER extends XRayVision> void useXRayEyes(SuperHero<POWER> p) {
		p.getPower().seeThroughWalls();
	}
	static <POWER extends SuperHearing & SuperSmell> void superFind(SuperHero<POWER> p) {
		p.getPower().hearSubtleNoises();
		p.getPower().trackBySmell();
	}
	
	public static void main(String[] args) {
		DogBoy db = new DogBoy();
		DogWomen dw = new DogWomen();
		useXRayEyes(dw);
		superFind(db);
		// You can do this:
		// List<? extends SuperHearing> audioBoys;
		// But you can’t do this:
		// List<? extends SuperHearing & SuperSmell> dogBoys;
		// Notice that wildcards (which we shall study next) are limited to a single bound.
	}
}

/*
 * Please read CovariantArrays.java next
 */
