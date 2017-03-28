/*
 * Please read Parcel4.java first
 */
// Nesting a class within a scope.
public class Parcel5 {
	private void internalTracking (boolean b) {
		if(b) {
			class TrackingSlip {
				private String s;
				TrackingSlip(String s) {
					this.s = s;
				}
				public String getSlip() {
					return s;
				}				
			}
			TrackingSlip ts = new TrackingSlip("Muscat");
			System.out.println(ts.getSlip());
		}
		//  Can't use it here! Out of scope:
		//! TrackingSlip ts1 = new TrackingSlip("x");
	}
	public void track () {
		internalTracking(true);
	}
	
	public static void main(String[] args) {
		Parcel5 pc5 = new Parcel5();
		pc5.track();
	}
}


/*
The class TrackingSlip is nested inside the scope of an if statement.
This does not mean that the class is conditionally created—it gets
compiled along with everything else. However, it’s not available outside
the scope in which it is defined. Other than that, it looks just like an
ordinary class.

After reading Parcel4 and Parcel5, i have reached a conclusion that a class that is nested
either inside a function or inside a scope, is not accessible outside the function or outside
its scope. But an object of that class is still easily available (like that of PDestination in Parcel4.java)
Such a class is built just like any other class at compile time. It is not built conditionally.

Parcel6.java next
*/
