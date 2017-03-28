package c08;

//: c08:Wrapping.java
public class Wrapping {
	private int i;
	public Wrapping(int x) { i = x; }
	public int value() { return i; }
	public void display() {
		System.out.println(i);		
	}
} ///:~