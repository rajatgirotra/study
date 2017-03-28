/*
 * Please read Joining.java first
 * Use threads to demonstrate a responsive command line user interface. 
 * Remember that one of the main reasons to introduce threading was to enable responsive GUI's. 
 */

class UnresponsiveUI {
	private static volatile double d = 1;
	public UnresponsiveUI() throws Exception {
		while(d > 0)
			d = d + (Math.PI + Math.E) / d;
		System.in.read(); // Never gets here
	}
}
public class ResponsiveUI extends Thread {
	private static volatile double d = 1;
	public ResponsiveUI() {
		setDaemon(true);
		start();
	}
	public void run() {
		while(d > 0)
			d = d + (Math.PI + Math.E) / d;		
	}
	
	public static void main(String[] args) throws Exception {
		//new UnresponsiveUI(); //--> Will need to kill the JAVA process if this is uncommented.
		new ResponsiveUI();
		System.in.read();
		System.out.println(d); // -->> show progress
		System.out.println(d); // -->> show progress
		System.out.println(d); // -->> show progress
		System.out.println(d); // -->> show progress
	}
}

/*
Please read ExceptionThread.java next
*/