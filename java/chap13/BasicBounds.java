/*
 * Please read Must_read_6.txt first
 */

import java.awt.Color;

interface HasColor {
	java.awt.Color getColor();	
}

interface Weight {
	int getWeight();
}

class Dimension {
	public int x, y, z;
}

class Colored<T extends HasColor> {
	T item;
	Colored(T item) {
		this.item = item;
	}
	public T get() {
		return item;
	}
	public void set(T item) {
		this.item = item;
	}
	java.awt.Color color() {
		return item.getColor();
	}
}

//This wont work Class first, then followed by interfaces
//class ColoredDimension<T extends HasColor & Dimension> {}

class ColoredDimension<T extends Dimension & HasColor> {
	T item;
	ColoredDimension(T item) {
		this.item = item;
	}
	public T get() {
		return item;
	}
	public void set(T item) {
		this.item = item;
	}
	java.awt.Color color() {
		return item.getColor();
	}
	int getX() {
		return item.x;
	}
}

class Solid<T extends Dimension & HasColor & Weight> {  //-->> multiple bounds.
	T item;
	Solid(T item) {
		this.item = item;
	}
	public T get() {
		return item;
	}
	public void set(T item) {
		this.item = item;
	}
	java.awt.Color color() {
		return item.getColor();
	}
	public int getX() {
		return item.x;
	}
	public int getY() {
		return item.y;
	}
	public int getZ() {
		return item.z;
	}
	int getWeight() {
		return item.getWeight();
	}
}

class Bounded extends Dimension implements HasColor, Weight {
	public Color getColor() {
		return null;
	}
	public int getWeight() {
		return 0;
	}

}

public class BasicBounds {
	public static void main(String[] args) {
		Solid<Bounded> ref = new Solid<Bounded>(new Bounded());		
		System.out.println(ref.color());
		System.out.println(ref.getWeight());
		System.out.println(ref.getX());
		
		//ColoredDimension<Bounded> cRef = new ColoredDimension<Bounded>(new Bounded());
	}
}

/*
 * You might observe that BasicBounds.java seems to contain redundancies that could be eliminated through inheritance. 
 * Next, you can see how each level of inheritance also adds bounds constraints
 * 
 * Please read InheritBounds.java next
 */
