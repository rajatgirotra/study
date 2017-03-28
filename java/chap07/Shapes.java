//: c07:Shapes.java
// Polymorphism in Java.
import java.util.*;
class Shape {
	void draw() {}
	void erase() {}
}
class Circle extends Shape {
	void draw() {
		System.out.println("Circle.draw()");
	}
	void erase() {
		System.out.println("Circle.erase()");
	}
}
class Square extends Shape {
	void draw() {
		System.out.println("Square.draw()");
	}
	void erase() {
		System.out.println("Square.erase()");
	}
}
class Triangle extends Shape {
	void draw() {
		System.out.println("Triangle.draw()");
	}
	void erase() {
		System.out.println("Triangle.erase()");
	}
}
// A "factory" that randomly creates shapes:
class RandomShapeGenerator {
	private Random rand = new Random();
	public Shape next() {
		switch(rand.nextInt(3)) {
			default:
			case 0: return new Circle();
			case 1: return new Square();
			case 2: return new Triangle();
		}
	}
}
public class Shapes {
	private static RandomShapeGenerator gen = new RandomShapeGenerator();

	public static void main(String[] args) {
		Shape[] s = new Shape[9];
		// Fill up the array with shapes:
		for(int i = 0; i < s.length; i++)
			s[i] = gen.next();
		// Make polymorphic method calls:
		for(int i = 0; i < s.length; i++)
			s[i].draw();
	}
}


