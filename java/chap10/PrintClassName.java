import java.util.*;

public class PrintClassName {
	public static void main(String[] args) {
		PrintClassName obj = new PrintClassName();
		printClassName(obj);
	}

	public static void printClassName(Object obj) {
		System.out.println("The name of the class " + obj + " is: " + obj.getClass().getName());
	}
}

	
