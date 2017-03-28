public class Dbl {
	public static void main(String[] args) {
		double d = 0;
		for (int i = 0; i< 10; ++i) {
			d += 0.1;
			System.out.println("dbl: " + d);
		}
	}
}

/*
This is an old problem because double and float are represented
as binary fractions according to IEEE 754 spec, so they cant be represented exactly.
Use DecimalFormat class to format it as required.
*/
