/*
 * Please read ThreeTuple.java first
 * 
 */
public class FourTuple<A, B, C, D> extends ThreeTuple<A, B, C>{
	public final D fourth;
	FourTuple(A a, B b, C c, D d) {
		super(a,b,c);
		fourth = d;
	}
	public String toString() {
		return "(" + first + ", " + second + ", " + third + ", " + fourth + ")";
	}
}
/*
Please read FiveTuple.java next
*/