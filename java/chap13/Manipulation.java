/*
 * Please read HasF.java first
 */

//class Manipulator<T extends HasF> {
class Manipulator<T> {
	private T obj;
	Manipulator(T obj) {
		this.obj = obj;
	}
	
	//Error - wont compile
	//The method f() is undefined for the type T
	public void manipulate() {
		obj.f();
	}
}
public class Manipulation {
	public static void main(String[] args) {
		HasF hf = new HasF();
		Manipulator<HasF> mhf = new Manipulator<HasF>(hf);
		mhf.manipulate();
	}
}

/*
Because of erasure, the Java compiler can’t map the requirement that manipulate( ) must be able to call f( ) on obj to
the fact that HasF has a method f( ). In order to call f( ), we must assist the generic class by giving it a bound that
tells the compiler to only accept types that conform to that bound. This reuses the extends keyword. Because of the bound,
Manipulator2.java compiles

Please read Manipulator2.java next
*/
