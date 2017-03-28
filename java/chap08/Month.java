/*
 * Please read Must_Read_1.txt first
 */
import java.util.*;

public class Month {
	private String mnth;

	//Note the private c'tor.
	private Month(String mnth) {
		this.mnth = mnth;
	}
	
	public static final Month
		ILL = new Month("ILLEGAL MONTH"),
		JAN = new Month("January"),
		FEB = new Month("February"),
		MAR = new Month("March"),
		APR = new Month("April"),
		MAY = new Month("May"),
		JUN = new Month("June"),
		JUL = new Month("July"),
		AUG = new Month("August"),
		SEP = new Month("September"),
		OCT = new Month("October"),
		NOV = new Month("November"),
		DEC = new Month("December");
	
	public static final Month[] months = {
		ILL, JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
	
	public String toString() {
		return mnth;
	}
	
	public static Month number(int ord) {
		return months[ord];
	}
	
	public static void main(String[] args) {
		Month m = Month.JAN;
		System.out.println(m);
		m = Month.number(12);
		System.out.println(m);
		System.out.println(m == Month.DEC); // true as both refer to the same object.
		System.out.println(m.equals(Month.DEC)); //true as both refer to the same object.
		System.out.println(Month.months[3]);
		}
}

/*
Please read TestMonths.java next
*/
