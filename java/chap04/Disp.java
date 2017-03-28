class B {int i;}

public class Disp {

	static void print(Object[] x) {
		for(int i = 0; i < x.length; ++i)
			System.out.println(x[i]);
	}

	public static void main(String[] args) {
		print(new Object[] {
				new Integer(100), new Disp(),
				new Float(22.7), new Double(1.01010101)
			});

		print(new Object[] { "one", "two", "three" });
		print(new Object[] { new B(), new B() } );
	}
}
