/* 
 * Please read Tuple.java first.
 */

public class TupleTest2 {
	static TwoTuple<String, Integer> f() {
		return Tuple.tuple("hi", 47);
	}
	static TwoTuple f2() {
		return Tuple.tuple("hi", 47);
	}
	static ThreeTuple<Float, String, Integer> g() {
		return Tuple.tuple(1.3f, "bye", 56);
	}
	static FourTuple<Boolean, String, Integer, Character> h() {
		return Tuple.tuple(false, "cruel world!!", 67, 'c');
	}
	
	static FiveTuple<Boolean, Double, Float, Character, Integer> i() {
		return Tuple.tuple(true, 67.98, 2.2f, 's', 0);
	}
	
	public static void main(String[] args) {
		TwoTuple<String,Integer> ttsi = f();
		//TwoTuple<String,Integer> tts = f2();
		System.out.println(ttsi);
		System.out.println(f2());
		System.out.println(g());
		System.out.println(h());
		System.out.println(i());		
	}
}

/*
Very straight forward. One thing to notice though. f() returns a parameterized type whereas f2()
returns an unparameterized type. You can basically say that in f2() you are doing:

TwoTuple ref = new TwoTuple<String, Integer>("hi", 47);

which you can say is kind of upcasting. So the compiler is OK with it.
But later if you do a kind of downcast like.

TwoTuple<String, Integer> paramRef = ref;

the compiler will issue you a warning.
i.e. the line which is commented above will cause a warning.

Please read TupleTest.java next
*/