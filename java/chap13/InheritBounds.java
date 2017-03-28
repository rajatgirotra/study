import java.awt.Color;

/*
 * Please read BasicBounds.java first.
 */

class HoldItem<T> {
	private T item;
	HoldItem(T item) {
		this.item = item;
	}
	T getItem() {
		return item;
	}
}

class Colored2<T extends HasColor> extends HoldItem<T> {
	Colored2(T item) {
		super(item);
	}
	public java.awt.Color color() {
		return getItem().getColor();
	}
}

class ColoredDimension2<T extends Dimension & HasColor> extends Colored2<T> {
	ColoredDimension2(T item) {
		super(item);
	}
	public int getX() {
		return getItem().x;
	}
	public int getY() {
		return getItem().y;
	}
	public int getZ() {
		return getItem().z;
	}
}

class Solid2<T extends Dimension & HasColor & Weight> extends ColoredDimension2<T> {
	Solid2(T item) {
		super(item);
	}
	public int getWeight() {
		return getItem().getWeight();
	}
}

class Bounded2 extends Dimension implements HasColor, Weight {
	public int getWeight() {
		return 78;
	}
	public java.awt.Color getColor() {
		return Color.ORANGE;
	}
}

public class InheritBounds {
	public static void main(String[] args) {
		Solid2<Bounded2> ref = new Solid2<Bounded2>(new Bounded2());
		System.out.println(ref.getWeight());
		System.out.println(ref.color().toString());
		System.out.println(ref.getX());
		System.out.println(ref.getY());
		System.out.println(ref.getZ());
	}
}

/*
Please read EpicBattle.java next
*/