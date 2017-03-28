import java.util.*;

class Base {
	public void foo() {
		System.out.println("Base::foo()");
	}
}

class Derv extends Base {
	public void foo() {
		System.out.println("Derv::foo()");
	}
}

public class TestInstanceOf {
	public static void main(String[] args) {
		Base poBase = new Derv();

		System.out.println(poBase instanceof Base);
		System.out.println(poBase instanceof Derv);
	}
}

