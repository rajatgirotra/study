/*
As a brief review of polymorphism and upcasting, you might code poly-morphism
as follows:
*/

import java.util.*;

class Shape {
	public void draw() {
		System.out.println(this + ".draw()");
	}
}
class Circle extends Shape {
	public String toString() {
		return "Circle";
	}
}
class Square extends Shape {
	public String toString() {
		return "Square";
	}
}
class Triangle extends Shape {
	public String toString() {
		return "Triangle";
	}
}
public class Shapes {
	public static void main(String[] args) {
		Shape[] shapeList = { new Circle(),
				               new Square(),
				               new Triangle()
							  };
		for(int i = 0; i < shapeList.length; ++i) {
			shapeList[i].draw();
		}
	}
}
