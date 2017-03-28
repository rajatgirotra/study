/*
 * Please read Holder.java first
 * One use of Generics is to use it to return more than one value from a function. Each of these values can be of any type.
 * See TwoTuple, ThreeTuple, FourTuple etc etc. and TupleTest for more.
 */
public class TwoTuple<A, B> {
	public final A first;
	public final B second;
	TwoTuple(A a, B b) {
		first = a;
		second = b;
	}
	public String toString() {
		return "(" + first + ", " + second + ")";
	}
}
/*
Please read ThreeTuple.java next
*/