/*
 * Please read TwoTuple.java first
 * 
 */
public class ThreeTuple<A, B, C> extends TwoTuple<A, B>{
	public final C third;
	ThreeTuple(A a, B b, C c) {
		super(a,b);
		third = c;
	}
	public String toString() {
		return "(" + first + ", " + second + ", " + third +")";
	}
}
/*
Please read FourTuple.java next
*/