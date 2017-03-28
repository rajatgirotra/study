/*
 * Please read Parcel2.java first
 */
import c08.Contents;
import c08.Destination;
import java.util.*;

class Parcel3 {
	private class PContents implements Contents {
		private int i = 11;
		public int value() {
			return i;
		}		
	}
	
	protected class PDestination implements Destination {
		private String s;
		PDestination(String s) {
			this.s = s;
		}
		public String readLabel() {
			return s;
		}
	}
	
	public Destination dest(String s) {
		return new PDestination(s);
	}
	
	public Contents cont() {
		return new PContents();
	}	
}

public class TestParcel {
	public static void main(String[] args) {
		Parcel3 pc3 = new Parcel3();
		Contents c = pc3.cont();
		Destination d = pc3.dest("Frankfurt");
		//!! Illegal.. Cannot access private Parcel3.PContents
		//!! Parcel3.PContents pc = (Parcel3.PContents)pc3.cont();
		Parcel3.PDestination pd = (Parcel3.PDestination)pc3.dest("Vietnam");
	}
}

/* 
How is a protected class accessible inside TestParcel when TestParcel does not extend Parcel3

 Please read Must_Read_4.txt next
*/
