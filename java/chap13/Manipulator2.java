/*
 * Please read Manipulator.java first
 */
class Manipulator2<T extends HasF> {
	private T obj;
	public Manipulator2(T x) { obj = x; }
	public void manipulate() { obj.f(); }
	
	public static void main(String[] args) {
		HasF hf = new HasF();
		Manipulator2<HasF> mhf = new Manipulator2<HasF>(hf);
		mhf.manipulate();
	}
}

/*
 * The bound <T extends HasF> says that T must be of type HasF or something derived from HasF. If this is true, then it is
 * safe to call f() on obj.
 * Please read Must_Read_2.txt next
 */